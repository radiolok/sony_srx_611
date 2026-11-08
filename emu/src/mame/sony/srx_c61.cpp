// license:BSD-3-Clause
// copyright-holders:SRX-611 reverse-engineering project
/***************************************************************************

    Sony SRX-611 SCARA robot controller

    Whole-system model running the original firmware of every board:
      - CPU board      : Intel 80486 (i486DX2) + boot EPROM + 1 MB flash
      - SERVO board    : NEC V810 (uPD70732) + 256 KB flash
      - Control board  : 2x ADSP-2115 (current loop / 3-phase PWM)
      - Teach pendant  : HD64180 (optional, not yet modelled)

    See doc/emulator_plan.md in the project repository.

    Stage 0: skeleton.  All four CPUs are declared, firmware is loaded, and
    the known RAM/ROM regions are mapped.  Everything else is an unmapped
    access (MAME logs these to error.log under -log), which acts as the
    trace stub of plan section 7.

    Stage 2: Control board models.
      - boot page 0 is loaded by machine_start(); BFORCE writes to SYSCNTL
        (DM 0x3FFF bit 9) reload BPAGE (bits 6-8) and reset the core while
        keeping the DAG registers, exactly like the real chip;
      - CXD8501R: 64 shared words at DM 0x3000-0x303F (mailbox, control,
        24-bit position counters, driver IDs, PWM);
      - AD7874: four sequential reads at DM 0x3400;
      - IRQ1 (ADC end-of-conversion) and IRQ2 (supervision tick) are driven
        by timers at guessed rates (plan section 4: both still unmeasured).

    Stage 3 (this file): SERVO <-> Control board windows.
      - V810 program space 0x400000/0x400080 = DSP DM $3000-$303F of DSP 1/2
        (doc/servo_dsp_link.md section 1): 64 16-bit words, word n at byte
        2n.  Both windows are routed to the very same cxd8501r_model arrays
        the DSP data maps use, so a command written by the V810 is executed
        by the DSP firmware and its write-back of 0 is what the V810 polls.
        No protocol logic is duplicated.
      - The absolute-encoder/SPORT0 path stays a documented stub (plan
        section 5.6 / doc/abs_encoder_protocol.md); no frame format is
        invented here.

    A temporary self-test (SRX_STAGE3_SELFTEST) drives the window handlers
    with 0x8001/0x8002/0x8000 and reads the ack back through the same window.
    It is needed because the SERVO monitor console is still gated on the
    DPRAM host handshake (stage 1 finding), so it cannot issue CONNECT by
    itself yet.  Remove it when the CPU side drives the handshake (stage 5).

    Stage 5 (this file): the whole system.
      - The SERVO slot DPRAM is now a real 4 KB dual-port RAM shared by the
        i486 slot window (0x700000, slot 1) and the V810 (0x200000), with an
        explicit mailbox at +0xFFC.  A V810 mailbox write asserts master IR4
        (slot 1) and the CPU ISR read of +0xFFC acknowledges it; a CPU mailbox
        write asserts a V810 external line (line 10, guessed -- plan 6.4 is
        still open, see V810_DPRAM_IRQ below).  The handshake (+0x04),
        doorbell (+0x10), servo-on bits (+0x14), axis mask (+0x18), status
        (+0x1C), parameter (+0x20) and per-axis blocks (+0x100*(k+1)) are just
        shared bytes: both firmwares already implement the protocol, so no
        protocol logic is added here (plan 7.3).
      - Slots 2/3 model kind-3 I/O boards: the header comes from the SYST
        scan at 0x108FC (info nibbles = input/output groups, input words at
        +4, output words at +4+lo_nibble).  Their input word 0 is the field
        input image, in which bit 6 is the DSS input (E401).  Outputs are
        latched and logged.
      - The safety chain (E-stop, DSS, AMPRDY, over-speed) is driven from
        Lua through CPU I/O ports 0xF0-0xF7.  Safe defaults are all-clear.
        The DSS state is injected into the I/O input image (bit 6), the DSP
        FLAG_IN / $3021 / $303F status (default clear, so stage 2/3 behaviour
        is unchanged) and the SERVO register stub.  See emu/tests/.

    Stage 6: external fault injection.
      - The safety register at CPU I/O ports 0xF0-0xF7 is extended to the
        six plan 5.7 fault classes: E-stop, DSS off, AMPRDY, over-speed,
        driver fault and ADC offset.  Safe defaults stay all-clear.
      - DSS is wired to the firmware's own system-input image: flipping it
        drives field-input word bit 6, and the running SYST task's I/O scan
        (0x108FC, called from 0x7E8D) copies that bit into RAM 0x62B8 bit 6,
        the exact input app_10C5C(7) reads in app_3BD28 (0x3BD28).
      - E-stop, AMPRDY, over-speed and driver fault are injected into the
        per-axis servo status dword (slot DPRAM +0x100*(k+1), word +0), whose
        bits the SVT AMP-status parser (0x3B8B8) turns into errors: bit
        0x1000 -> E300, 0x0400 -> E340, 0x80000 -> E341, 0x4000 -> E400
        (error constant 0x190 at 0x3BAF5).  DSS/E401 uses the system input.
      - ADC offset (port 0xF7, signed) offsets every AD7874 channel.
      - Whether the firmware actually *raises* the error is a separate
        question; see the stage 6 test and doc/emulator_plan.md section 8.

    Stage 7: the real teach pendant.
      - A Z180 (HD64180-compatible Z80180) runs the TP EPROM from 0 with 32 KB
        of RAM at 0x8000.  Its ASCI channel 0 is wired directly to the CPU
        board's ch1 8251A, so the two real firmwares perform the
        "SRX6" <-> "TP4" handshake themselves (the pty card on ch1 stays
        available as an optional monitor/injection peer).
      - External I/O 0x80-0x83 models the key matrix/panel latch and
        0xC0/0xC1 a 20x4 HD44780-compatible character LCD.  The 20-character
        lines are logged when they change and can be read from Lua through
        CPU I/O ports 0xFA/0xFB; keys are injected through 0xF8/0xF9.
      - Unknowns from doc/TP_firmware_structure.md are modelled only as far
        as the firmware needs; the LCD type and the exact key matrix are
        inferred, not confirmed on hardware (see the report).

    Stage 4: CPU-board peripherals.
      - 3x 8251A: ch1 0xC0/C4 teach pendant, ch2 0xC8/CC PC host,
        ch3 0xD0/D4 user RS-232C.  Each has an rs232_port slot whose default
        card is "pty" (pseudo terminal), so an external program can drive the
        pendant / SRXWIN protocol.  Counter 2 of the 8254 clocks ch1+ch2,
        counter 1 clocks ch3 (architecture report 6.1).
      - 8254 at 0xB0-0xBC, 3.072 MHz input; counter 0 = 100 Hz system tick
        -> slave PIC IR2, counters 1/2 = serial baud clocks.
      - 2x 8259A: master 0xA0/A4, slave 0xA8/AC cascaded on master IR7,
        vectors 0x20/0x28, IRQ lines wired as architecture report 4.3.
      - MSM6242 RTC at 0x60-0x9C (16 BCD registers, stride 4).
      - 8 KB EEPROM at 0x600000, busy/status port 0x0C.  The real contents
        are NOT available (plan 6.1, P1).  A blank (0xFF) image is filled
        from an optional "eeprom.bin" ROM in the "eeprom" region; drop a
        real dump in the ROM set with that name to use it.  The 8 KB are
        battery-free non-volatile storage: MAME saves them on exit as
        nvram/srx_c61/eeprom_nv (raw 8192-byte image, same layout as the chip)
        and reloads them on the next start, so parameters entered on the
        pendant or loaded as a .CTR file survive.  The ROM image is only the
        default used when no saved file exists (delete the file to reload
        it).  Port 0x0C bit 6 = write complete (the driver at 0x6B1C polls it
        after each 32-byte page and reports 0x7919 if it stays clear).
      - PC-card window 0x200000 returns 0xFF ("no card"), port 0x4C bit 0 =
        attribute-memory select (stored and logged).
      - Slot latches 0x30/34/38/3C/40 (stored and logged), five 64 KB slot
        DPRAM windows at 0x700000 + (s-1)*0x10000 as plain RAM.  Slot 1 is
        initialised as a servo board (kind byte 1), slots 2/3 as I/O boards
        (kind 3), slots 4/5 empty -- this is the plan 5.2 population guess
        and must be confirmed (plan 6.13).  The MB8421 mailbox/IRQ behaviour
        stays stage 5.  The optional SIO2 board at 0x2000000 is absent; the
        firmware probe (0x7E24) tolerates it (reads != 0x0500).

    TODO (plan milestones):
      1. SERVO monitor UART (banner string at ROM offset 0x21CDA) -> TCP terminal
      2. Control-board CXD8501R + AD7874 models, DSP boot pages + BFORCE, IRQ1/2
      3. SERVO <-> Control windows 0x400000/0x400080
      4. CPU 8251/8254/8259, RTC, EEPROM image, PC card, slot kind bytes
      5. CPU <-> SERVO DPRAM + IRQs, I/O boards, plant, safety panel
      6. Plant: PWM -> current -> motion, encoder frames (plan 5.6)

***************************************************************************/

#include "emu.h"

#include "cpu/i386/i386.h"
#include "cpu/v810/v810.h"
#include "cpu/adsp2100/adsp2100.h"
#include "cpu/z180/z180.h"

#include "bus/rs232/rs232.h"
#include "machine/i8251.h"
#include "machine/msm6242.h"
#include "machine/nvram.h"
#include "machine/pic8259.h"
#include "machine/pit8253.h"

#include "dipty.h"

#include <algorithm>
#include <iterator>


// The pendant controller is a Hitachi HD64180, which MAME models as the
// Z80180.  The TP firmware programs CNTLB0 = 0x07 (SS = 111); MAME's Z180
// treats SS = 111 as "external clock", which would leave the ASCI without a bit
// rate.  The firmware clearly expects a 9600 8N2 link (the CPU board's 8251A
// runs at 9600), so translate that one write to SS = 001:
// MAME's ASCI clock is CPU/2 = 3.072 MHz, giving 9600 baud with
// 3.072 MHz / (2*10) / 16.  This is a model assumption [H], not a hardware-confirmed
// register value; it does not change any other internal register access.
class srx_tp_z180_device : public z80180_device
{
public:
	srx_tp_z180_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
		: z80180_device(mconfig, tag, owner, clock)
		, m_tp_rx_log(0)
		, m_tp_tx_log(0)
		, m_tp_tx_hist(0)
		, m_tp_handshake(false)
	{
	}

protected:
	virtual uint8_t z180_internal_port_read(uint8_t port) override
	{
		uint8_t data = z80180_device::z180_internal_port_read(port);
		// The TP's DCD0 input is not connected in this model (there is no
		// modem-control line in the pendant cable), but MAME's ASCI leaves the
		// DCD0 status bit uninitialised/reset-preserved at 1, which would trap
		// the firmware in its boot wait loop at 0x0114 and make ISR B ignore
		// received bytes.  Force it clear.
		if (port == 0x04)
			data &= ~0x04;
		if (port == 0x08 && m_tp_rx_log++ < 32)
			logerror("SRX TP ASCI RX byte 0x%02X (%c)\n", data,
					(data >= 0x20 && data < 0x7f) ? char(data) : '.');
		return data;
	}

	virtual void z180_internal_port_write(uint8_t port, uint8_t data) override
	{
		if (port == 0x06)
		{
			if (m_tp_tx_log++ < 32)
				logerror("SRX TP ASCI TX byte 0x%02X (%c)\n", data,
						(data >= 0x20 && data < 0x7f) ? char(data) : '.');
			// Detect the identity reply 1B 07 01 00 'T' 'P' '4'.
			m_tp_tx_hist = (m_tp_tx_hist << 8) | data;
			if ((m_tp_tx_hist & 0x00ffffffffffffffULL) == 0x001b070100545034ULL
					&& !m_tp_handshake)
			{
				m_tp_handshake = true;
				logerror("SRX TP: TP4 handshake reply sent by the pendant firmware\n");
			}
		}
		if (port == 0x02)
		{
			if (data == 0x07)
				data = 0x01;
			logerror("SRX TP: ASCI CNTLB0 <- 0x%02X (9600 8N2 model)\n", data);
		}
		z80180_device::z180_internal_port_write(port, data);
	}

public:
	bool handshake_seen() const { return m_tp_handshake; }

private:
	unsigned m_tp_rx_log;
	unsigned m_tp_tx_log;
	uint64_t m_tp_tx_hist;
	bool m_tp_handshake;
};

DECLARE_DEVICE_TYPE(SRX_TP_Z180, srx_tp_z180_device)
DEFINE_DEVICE_TYPE(SRX_TP_Z180, srx_tp_z180_device, "srx_tp_z180", "Sony SRX-611 teach pendant (HD64180/Z180)")

namespace {

// Stage-3 bring-up test: drive the V810->DSP windows directly to prove the
// shared-register path and the command acknowledgement.  Stage 5 leaves it
// off: the CPU now drives the DPRAM handshake, so the SERVO firmware issues
// the CONNECT command itself.
#define SRX_STAGE3_SELFTEST 0

// V810 external interrupt line used for the CPU->SERVO mailbox.  The real
// line is unknown (plan 6.4: the 0x300000/0x500000 registers and the V810
// interrupt sources still have to be traced).  Line 10 is a plausible choice:
// its vector (ROM 0x17B8) touches the DSP windows, so it is one of the
// external/housekeeping vectors.  The CPU firmware only reads +0xFFC, so this
// line stays clear in normal operation unless a Lua/debug client writes the
// mailbox from the CPU side.
static constexpr int V810_DPRAM_IRQ = 10;

// Safety chain is a bitfield of *faults* (0 = all clear).  It is written by
// Lua through CPU I/O port 0xF0; see emu/tests/stage6_faults.lua.
//   0x01 E-stop active            -> servo status bit 0x00001000 (E300)
//   0x02 DSS off                  -> system input 0x62B8 bit 6 (E401)
//   0x04 AMPRDY fail              -> servo status bit 0x00080000 (E341)
//   0x08 SPD over-speed           -> servo status bit 0x00004000 (E400)
//   0x10 driver fault             -> servo status bit 0x00000400 (E340)
static constexpr uint8_t SAFETY_ESTOP        = 0x01;
static constexpr uint8_t SAFETY_DSS_OFF      = 0x02;
static constexpr uint8_t SAFETY_AMPRDY       = 0x04;
static constexpr uint8_t SAFETY_OVERSPEED    = 0x08;
static constexpr uint8_t SAFETY_DRIVER_FAULT = 0x10;
static constexpr uint8_t SAFETY_MASK         = 0x1f;

// Bits of the per-axis servo status dword (slot DPRAM +0x100*(k+1) +0x00)
// that the SVT AMP-status parser 0x3B8B8 decodes.  Values and error codes are
// from that function's tests (addresses are the mov of the error constant):
//   0x00001000 -> 0x12C E300 emergency stop      (0x3B8FA)
//   0x00000400 -> 0x154 E340 AMP WDT             (0x3B9AB / 0x3B9C0)
//   0x00080000 -> 0x155 E341 AMP Ready           (0x3B9C7 / 0x3B9D4)
//   0x00004000 -> 0x190 E400 SPD over-speed      (0x3BAE5 / 0x3BAF1)
static constexpr uint32_t SERVO_ST_ESTOP        = 0x00001000;
static constexpr uint32_t SERVO_ST_AMP_WDT      = 0x00000400;
static constexpr uint32_t SERVO_ST_OVERSPEED    = 0x00004000;
static constexpr uint32_t SERVO_ST_AMPRDY       = 0x00080000;

// Guessed interrupt rates.  The real sources are still to be measured
// (plan section 4); only the ratios matter for keeping timeouts quiet.
static constexpr int DSP_IRQ1_HZ = 8000;    // ADC end-of-conversion / current loop
static constexpr int DSP_IRQ2_HZ = 8000;    // supervision tick (heartbeat every 0x2000 ticks)


// ------------------------------------------------------------------------
//  Slot window state
// ------------------------------------------------------------------------
//  Every slot has a 4 KB dual-port window (2x MB8421 on the real board).
//  Slot 1 is shared with the V810; slots 2/3 are kind-3 I/O boards; slots
//  4/5 are empty.  The model is plain shared storage plus explicit mailbox
//  IRQ bits, because the real mailbox addresses are the firmware-defined
//  +0xFFC word rather than the MB8421 fixed last-two-word mailbox.
struct slot_window
{
	uint8_t ram[0x1000];
	uint8_t mailbox;
	bool cpu_irq;           // SERVO -> CPU interrupt pending
	bool servo_irq;         // CPU -> SERVO interrupt pending
	uint16_t field_out;     // last output word written by the CPU
	unsigned irq_asserts;
	unsigned handshake_writes;
	unsigned handshake_reads;
	unsigned doorbell_writes;
	unsigned output_writes;
};



// ------------------------------------------------------------------------
//  CXD8501R - 64 x 16-bit register file shared by the DSP and the V810
// ------------------------------------------------------------------------
struct cxd8501r_model
{
	uint16_t regs[0x40];

	void reset()
	{
		std::fill(std::begin(regs), std::end(regs), 0);
		regs[0x30] = 0x1918;    // driver module IDs 8/9, ready bits 0x1010 (active low = ready)
		regs[0x33] = 0x03e8;    // PWM carrier period, 1000 as set by page 1
		for (int i = 0; i < 6; i++)
			regs[0x37 + i] = 500;   // six compares at 50% -> zero voltage
	}
};


class srx_c61_state : public driver_device
{
public:
	srx_c61_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag)
		, m_maincpu(*this, "maincpu")
		, m_servocpu(*this, "servocpu")
		, m_dsp1(*this, "dsp1")
		, m_dsp2(*this, "dsp2")
		, m_tp(*this, "tp")
		, m_dsp1_pm(*this, "dsp1_pm")
		, m_dsp2_pm(*this, "dsp2_pm")
		, m_pit(*this, "pit")
		, m_pic_master(*this, "pic_master")
		, m_pic_slave(*this, "pic_slave")
		, m_uart(*this, "uart%u", 0U)
		, m_rs232(*this, "rs232_%u", 1U)
		, m_rtc(*this, "rtc")
		, m_eeprom_nv(*this, "eeprom_nv")
		, m_eeprom_ram(*this, "eeprom_ram")
	{
	}

	void srx_c61(machine_config &config);

protected:
	virtual void machine_start() override ATTR_COLD;

private:
	required_device<i486_device> m_maincpu;
	required_device<v810_device> m_servocpu;
	required_device<adsp2115_device> m_dsp1;
	required_device<adsp2115_device> m_dsp2;
	required_device<srx_tp_z180_device> m_tp;
	required_shared_ptr<uint32_t> m_dsp1_pm;
	required_shared_ptr<uint32_t> m_dsp2_pm;

	// stage 4: CPU board peripherals
	required_device<pit8254_device> m_pit;
	required_device<pic8259_device> m_pic_master;
	required_device<pic8259_device> m_pic_slave;
	required_device_array<i8251_device, 3> m_uart;
	required_device_array<rs232_port_device, 3> m_rs232;
	required_device<msm6242_device> m_rtc;
	required_device<nvram_device> m_eeprom_nv;
	required_shared_ptr<uint32_t> m_eeprom_ram;

	void maincpu_map(address_map &map);
	void maincpu_io_map(address_map &map);
	void servocpu_map(address_map &map);
	void dsp1_program_map(address_map &map);
	void dsp1_data_map(address_map &map);
	void dsp2_program_map(address_map &map);
	void dsp2_data_map(address_map &map);
	void tp_program_map(address_map &map);
	void tp_io_map(address_map &map);

	uint8_t diag_io_r();
	void diag_io_w(uint8_t data);

	// stage 4: CPU board I/O handlers
	uint8_t pit_r(offs_t offset);
	void pit_w(offs_t offset, uint8_t data);
	uint8_t pic_master_r(offs_t offset);
	void pic_master_w(offs_t offset, uint8_t data);
	uint8_t pic_slave_r(offs_t offset);
	void pic_slave_w(offs_t offset, uint8_t data);
	uint8_t rtc_r(offs_t offset);
	void rtc_w(offs_t offset, uint8_t data);
	uint8_t sys_input0_r();
	uint8_t sys_input1_r();
	uint8_t eeprom_status_r();
	void eeprom_status_w(uint8_t data);
	void eeprom_nvram_init(nvram_device &nvram, void *data, size_t size);
	uint8_t pccard_attr_r();
	void pccard_attr_w(uint8_t data);
	uint8_t pccard_r(offs_t offset);
	void pccard_w(offs_t offset, uint8_t data);
	uint8_t slot_latch_r(offs_t offset);
	void slot_latch_w(offs_t offset, uint8_t data);
	void flash_w(offs_t offset, uint32_t data, uint32_t mem_mask);
	void pit_out0_w(int state);
	void pit_out1_w(int state);
	void pit_out2_w(int state);
	void blitter_stub_w(offs_t offset, uint8_t data);

	// stage 5: slot windows, I/O boards, safety/field-I/O panel
	uint32_t slot_r(int slot, offs_t offset, uint32_t mem_mask);
	void slot_w(int slot, offs_t offset, uint32_t data, uint32_t mem_mask);
	uint32_t slot1_r(offs_t offset, uint32_t mem_mask) { return slot_r(0, offset, mem_mask); }
	void slot1_w(offs_t offset, uint32_t data, uint32_t mem_mask) { slot_w(0, offset, data, mem_mask); }
	uint32_t slot2_r(offs_t offset, uint32_t mem_mask) { return slot_r(1, offset, mem_mask); }
	void slot2_w(offs_t offset, uint32_t data, uint32_t mem_mask) { slot_w(1, offset, data, mem_mask); }
	uint32_t slot3_r(offs_t offset, uint32_t mem_mask) { return slot_r(2, offset, mem_mask); }
	void slot3_w(offs_t offset, uint32_t data, uint32_t mem_mask) { slot_w(2, offset, data, mem_mask); }
	uint32_t slot4_r(offs_t offset, uint32_t mem_mask) { return slot_r(3, offset, mem_mask); }
	void slot4_w(offs_t offset, uint32_t data, uint32_t mem_mask) { slot_w(3, offset, data, mem_mask); }
	uint32_t slot5_r(offs_t offset, uint32_t mem_mask) { return slot_r(4, offset, mem_mask); }
	void slot5_w(offs_t offset, uint32_t data, uint32_t mem_mask) { slot_w(4, offset, data, mem_mask); }

	uint32_t servo_dpram_r(offs_t offset, uint32_t mem_mask);
	void servo_dpram_w(offs_t offset, uint32_t data, uint32_t mem_mask);

	uint8_t lua_io_r(offs_t offset);
	void lua_io_w(offs_t offset, uint8_t data);
	void safety_changed();
	uint32_t servo_status_faults() const;
	uint8_t servo_status_byte(offs_t byteaddr, uint8_t stored) const;

	void slot_cpu_irq(int slot, bool state);
	uint8_t slot_io_read_byte(int slot, offs_t offset);
	void slot_io_write_byte(int slot, offs_t offset, uint8_t data);
	void slot_dpram_write_byte(int slot, offs_t offset, uint8_t data);
	uint8_t slot_dpram_read_byte(int slot, offs_t offset);

	// 8251 access wrappers with a bounded transmit/control trace.
	uint8_t uart_data_r(int ch);
	void uart_data_w(int ch, uint8_t data);
	uint8_t uart_status_r(int ch);
	void uart_ctrl_w(int ch, uint8_t data);
	uint8_t uart1_data_r() { return uart_data_r(0); }
	void uart1_data_w(uint8_t data) { uart_data_w(0, data); }
	uint8_t uart1_status_r() { return uart_status_r(0); }
	void uart1_ctrl_w(uint8_t data) { uart_ctrl_w(0, data); }
	uint8_t uart2_data_r() { return uart_data_r(1); }
	void uart2_data_w(uint8_t data) { uart_data_w(1, data); }
	uint8_t uart2_status_r() { return uart_status_r(1); }
	void uart2_ctrl_w(uint8_t data) { uart_ctrl_w(1, data); }
	uint8_t uart3_data_r() { return uart_data_r(2); }
	void uart3_data_w(uint8_t data) { uart_data_w(2, data); }
	uint8_t uart3_status_r() { return uart_status_r(2); }
	void uart3_ctrl_w(uint8_t data) { uart_ctrl_w(2, data); }
	void uart_cts_assert(int unused);
	void uart_txrdy_w(int ch, int state);
	void uart_rxrdy_w(int ch, int state);
	void uart1_txrdy_w(int state) { uart_txrdy_w(0, state); }
	void uart2_txrdy_w(int state) { uart_txrdy_w(1, state); }
	void uart3_txrdy_w(int state) { uart_txrdy_w(2, state); }
	void uart1_rxrdy_w(int state) { uart_rxrdy_w(0, state); }
	void uart2_rxrdy_w(int state) { uart_rxrdy_w(1, state); }
	void uart3_rxrdy_w(int state) { uart_rxrdy_w(2, state); }
	void uart1_txd_w(int state);
	void tp_status_check(int unused);

	// stage 7: teach pendant (Z180 + key matrix + character LCD)
	uint8_t tp_port80_r();
	void tp_port80_w(uint8_t data);
	uint8_t tp_port81_r();
	uint8_t tp_port82_r();
	void tp_port82_w(uint8_t data);
	uint8_t tp_port83_r();
	void tp_port83_w(uint8_t data);
	uint8_t tp_lcd_status_r();
	void tp_lcd_cmd_w(uint8_t data);
	uint8_t tp_lcd_data_r();
	void tp_lcd_data_w(uint8_t data);
	int tp_lcd_index(uint8_t addr) const;
	void tp_display_changed();

	uint8_t m_slot_latch[5];
	bool m_pccard_attr;
	unsigned m_flash_writes;
	unsigned m_pccard_writes;
	unsigned m_slot_latch_writes[5];
	unsigned m_tick_out;
	unsigned m_uart_tx_count[3];
	unsigned m_uart_ctrl_count[3];
	unsigned m_uart_txrdy_count[3];
	bool m_uart_initialized[3];
	unsigned m_sys_input_reads[2];
	emu_timer *m_cts_timer;
	emu_timer *m_tp_status_timer;

	// stage 5: shared slot windows + safety/field I/O
	slot_window m_slots[5];
	uint8_t m_safety_faults;
	uint16_t m_field_input;
	int8_t m_adc_offset;
	unsigned m_safety_logs;
	unsigned m_slot_dpram_irq_logs;
	unsigned m_adc_offset_logs;
	unsigned m_servo_status_logs;

	// stage 7: teach pendant state
	uint8_t m_tp_display[80];           // 4 lines x 20 characters, line-major
	char m_tp_display_last[4][21];
	uint8_t m_tp_cursor;
	bool m_tp_entry_increment;
	bool m_tp_display_on;
	uint8_t m_tp_port80;
	uint8_t m_tp_port82;
	uint8_t m_tp_port83;
	uint8_t m_tp_keys[7];               // bit set = key pressed in that column
	uint8_t m_tp_key_col;
	uint8_t m_tp_display_index;
	unsigned m_tp_key_scan_logs;

	// Stage 1: SERVO on-board peripheral block (0x300000..).  Writes are
	// logged; printable bytes are surfaced as console output.
	uint32_t servo_console_r(offs_t offset);
	void servo_console_w(offs_t offset, uint32_t data, uint32_t mem_mask);

	// Stage 3: SERVO DSP windows 0x400000/0x400080 -> CXD8501R register files.
	uint32_t servo_dsp_window_r(offs_t offset, uint32_t mem_mask);
	void servo_dsp_window_w(offs_t offset, uint32_t data, uint32_t mem_mask);

	// Stage 2: Control board (2x ADSP-2115)
	cxd8501r_model m_cxd[2];
	uint16_t m_adc[2][4];
	unsigned m_adc_index[2];
	uint16_t m_outlatch[2];
	uint16_t m_syscntl[2];
	bool m_page1_active[2];
	bool m_flagin_logged[2];
	uint8_t m_cxd_log_count[2][0x40];

	emu_timer *m_irq1_timer[2];
	emu_timer *m_irq2_timer[2];
	emu_timer *m_irq_clear_timer[2];
	emu_timer *m_adc_timer[2];
	emu_timer *m_selftest_timer;

	void dsp_boot_page(int which, int page);
	void dsp_irq1_tick(int which);
	void dsp_irq2_tick(int which);
	void dsp_irq_clear(int which);
	void dsp_adc_done(int which);
	void dsp_selftest(int unused);

	void dsp_set_line(int which, int line, int state);
	void dsp_set_flag_in(int which, int state);
	uint16_t dsp_cxd_r(int which, offs_t offset);
	void dsp_cxd_w(int which, offs_t offset, uint16_t data);
	uint16_t dsp_adc_r(int which);
	uint16_t dsp_latch_r(int which);
	void dsp_latch_w(int which, uint16_t data);
	uint16_t dsp_syscntl_r(int which);
	void dsp_syscntl_w(int which, uint16_t data);
	void dsp_cxd_log(int which, offs_t offset, uint16_t data);

	// address-map wrappers (one set per DSP)
	uint16_t dsp1_cxd_r(offs_t offset) { return dsp_cxd_r(0, offset); }
	void dsp1_cxd_w(offs_t offset, uint16_t data) { dsp_cxd_w(0, offset, data); }
	uint16_t dsp2_cxd_r(offs_t offset) { return dsp_cxd_r(1, offset); }
	void dsp2_cxd_w(offs_t offset, uint16_t data) { dsp_cxd_w(1, offset, data); }
	uint16_t dsp1_adc_r() { return dsp_adc_r(0); }
	uint16_t dsp2_adc_r() { return dsp_adc_r(1); }
	uint16_t dsp1_latch_r() { return dsp_latch_r(0); }
	void dsp1_latch_w(uint16_t data) { dsp_latch_w(0, data); }
	uint16_t dsp2_latch_r() { return dsp_latch_r(1); }
	void dsp2_latch_w(uint16_t data) { dsp_latch_w(1, data); }
	uint16_t dsp1_syscntl_r() { return dsp_syscntl_r(0); }
	void dsp1_syscntl_w(uint16_t data) { dsp_syscntl_w(0, data); }
	uint16_t dsp2_syscntl_r() { return dsp_syscntl_r(1); }
	void dsp2_syscntl_w(uint16_t data) { dsp_syscntl_w(1, data); }
};


/***************************************************************************
    Memory maps
***************************************************************************/

// CPU board (i486): flat 32-bit protected mode.  Runtime base is 0xFFE00000
// (file offset = runtime address - 0xFFE00000).
void srx_c61_state::maincpu_map(address_map &map)
{
	map(0x00000000, 0x001fffff).ram();                         // 2 MB SRAM at 0
	map(0x00200000, 0x002fffff).rw(FUNC(srx_c61_state::pccard_r), FUNC(srx_c61_state::pccard_w)); // PC card window (empty: reads 0xFF)
	map(0x00600000, 0x00601fff).ram().share(m_eeprom_ram);      // 8 KB EEPROM (nvram "eeprom_nv", saved on exit)

	// Stage 5: slot windows.  The first 4 KB of each 64 KB window is the
	// real dual-port RAM (2x MB8421); the rest of the window is unused stub
	// space.  Slot 1 is the SERVO board (shares its RAM with the V810),
	// slots 2/3 are kind-3 I/O boards, slots 4/5 are empty.
	map(0x00700000, 0x00700fff).rw(FUNC(srx_c61_state::slot1_r), FUNC(srx_c61_state::slot1_w));
	map(0x00701000, 0x0070ffff).ram();
	map(0x00710000, 0x00710fff).rw(FUNC(srx_c61_state::slot2_r), FUNC(srx_c61_state::slot2_w));
	map(0x00711000, 0x0071ffff).ram();
	map(0x00720000, 0x00720fff).rw(FUNC(srx_c61_state::slot3_r), FUNC(srx_c61_state::slot3_w));
	map(0x00721000, 0x0072ffff).ram();
	map(0x00730000, 0x00730fff).rw(FUNC(srx_c61_state::slot4_r), FUNC(srx_c61_state::slot4_w));
	map(0x00731000, 0x0073ffff).ram();
	map(0x00740000, 0x00740fff).rw(FUNC(srx_c61_state::slot5_r), FUNC(srx_c61_state::slot5_w));
	map(0x00741000, 0x0074ffff).ram();

	map(0xffe00000, 0xffefffff).rom().region("maincpu", 0).w(FUNC(srx_c61_state::flash_w)); // 1 MB main flash (ROM1-C.bin), writes logged
	map(0xffff8000, 0xffffffff).rom().region("boot", 0);       // 32 KB boot EPROM (reset vector)
}

void srx_c61_state::maincpu_io_map(address_map &map)
{
	map(0x0000, 0x0000).r(FUNC(srx_c61_state::sys_input0_r));  // CPU-board system input byte
	map(0x0008, 0x0008).r(FUNC(srx_c61_state::sys_input1_r));  // CPU-board system input/status byte
	map(0x000c, 0x000c).rw(FUNC(srx_c61_state::eeprom_status_r), FUNC(srx_c61_state::eeprom_status_w));
	map(0x0020, 0x0020).rw(FUNC(srx_c61_state::diag_io_r), FUNC(srx_c61_state::diag_io_w)); // diagnostic/halt-code port
	map(0x0024, 0x0024).w(FUNC(srx_c61_state::blitter_stub_w));  // boot EPROM writes 2 (unknown latch)
	map(0x0028, 0x0028).w(FUNC(srx_c61_state::blitter_stub_w));  // SIO2 scan writes 0..7 (unknown latch)
	map(0x0030, 0x0043).rw(FUNC(srx_c61_state::slot_latch_r), FUNC(srx_c61_state::slot_latch_w));
	map(0x004c, 0x004c).rw(FUNC(srx_c61_state::pccard_attr_r), FUNC(srx_c61_state::pccard_attr_w)); // PC card attribute select

	// 8259A pair: even port = command, odd (stride 4) = data
	map(0x00a0, 0x00a7).rw(FUNC(srx_c61_state::pic_master_r), FUNC(srx_c61_state::pic_master_w));
	map(0x00a8, 0x00af).rw(FUNC(srx_c61_state::pic_slave_r), FUNC(srx_c61_state::pic_slave_w));

	// 8254: counter 0/1/2 at 0xB0/0xB4/0xB8, control at 0xBC
	map(0x00b0, 0x00bf).rw(FUNC(srx_c61_state::pit_r), FUNC(srx_c61_state::pit_w));

	// RTC, 16 BCD registers with a 4-byte port stride
	map(0x0060, 0x009f).rw(FUNC(srx_c61_state::rtc_r), FUNC(srx_c61_state::rtc_w));

	// 8251A x3: data/status+control pairs, 4-byte port stride
	map(0x00c0, 0x00c0).rw(FUNC(srx_c61_state::uart1_data_r),   FUNC(srx_c61_state::uart1_data_w));
	map(0x00c4, 0x00c4).rw(FUNC(srx_c61_state::uart1_status_r), FUNC(srx_c61_state::uart1_ctrl_w));
	map(0x00c8, 0x00c8).rw(FUNC(srx_c61_state::uart2_data_r),   FUNC(srx_c61_state::uart2_data_w));
	map(0x00cc, 0x00cc).rw(FUNC(srx_c61_state::uart2_status_r), FUNC(srx_c61_state::uart2_ctrl_w));
	map(0x00d0, 0x00d0).rw(FUNC(srx_c61_state::uart3_data_r),   FUNC(srx_c61_state::uart3_data_w));
	map(0x00d4, 0x00d4).rw(FUNC(srx_c61_state::uart3_status_r), FUNC(srx_c61_state::uart3_ctrl_w));

	// Stage 5: Lua fault-injection / field-I/O panel.  These ports are not
	// used by the firmware (the highest decoded port is 0xD4).
	//   0xF0 safety fault bits (0 = all clear; see SAFETY_* above)
	//   0xF1/0xF2 field input word, low/high byte (raw override)
	//   0xF3/0xF4 last I/O-board output word, low/high byte (readback)
	//   0xF5 SERVO DPRAM mailbox byte
	//   0xF6 slot 1 IRQ pending (bit0 SERVO->CPU, bit1 CPU->SERVO)
	//   0xF7 ADC offset, signed 8-bit (added to every AD7874 channel)
	//   0xF8 TP key column select (0-6)
	//   0xF9 TP key rows for that column (bit set = pressed)
	//   0xFA TP display read index (0-79, line-major)
	//   0xFB TP display character at the index; reads auto-increment
	map(0x00f0, 0x00fb).rw(FUNC(srx_c61_state::lua_io_r), FUNC(srx_c61_state::lua_io_w));
}

// SERVO board (V810): ROM copied to RAM at 0 on boot.  gp = 0x2BAEC.
void srx_c61_state::servocpu_map(address_map &map)
{
	map(0x00000000, 0x0007ffff).ram();                         // 512 KB RAM at 0
	map(0x00100000, 0x0013ffff).rom().region("servocpu", 0);   // 256 KB flash (ROM_SERVO.bin)
	map(0xfffc0000, 0xffffffff).rom().region("servocpu", 0);   // reset alias (vector at 0xFFFFFFF0)

	// Stage 5: slot dual-port RAM shared with the CPU board (slot 1 window
	// at 0x700000).  The V810 firmware writes the header (+0/+1 = 0x0101),
	// polls +0x04 for the host handshake and +0x10 for the doorbell, and
	// writes the mailbox at +0xFFC.  See doc/servo_dsp_link.md section 1.
	map(0x00200000, 0x00200fff).rw(FUNC(srx_c61_state::servo_dpram_r), FUNC(srx_c61_state::servo_dpram_w));

	// Stage 1: on-board peripherals, modelled as register stubs so the monitor
	// runs without faulting.  The 0x30000x block is the baud/SCI setup.
	map(0x00300000, 0x0030000f).rw(FUNC(srx_c61_state::servo_console_r), FUNC(srx_c61_state::servo_console_w));
	map(0x00301000, 0x00301003).ram();                         // output latch (LEDs / enables)
	map(0x00302000, 0x00302003).ram();                         // DSP heartbeat / status
	map(0x00303000, 0x00303003).ram();
	map(0x00304000, 0x00304003).ram();
	map(0x00305000, 0x0030502f).ram();
	map(0x00307000, 0x00307003).ram();
	map(0x00308000, 0x003080ff).ram();                         // LEDs / DIP / status
	map(0x00309000, 0x00309003).ram();
	map(0x00318000, 0x0031803f).ram();
	map(0x00500000, 0x0050004f).ram();                         // CXD8477Q pair (stage 2/3)

	// Stage 3: DSP windows.  0x400000 = DSP 1 DM $3000-$303F, 0x400080 =
	// DSP 2, word n at byte 2n (doc/servo_dsp_link.md section 1).  Both go
	// straight to the CXD8501R register files used by the DSP data maps.
	map(0x00400000, 0x004000ff).rw(FUNC(srx_c61_state::servo_dsp_window_r), FUNC(srx_c61_state::servo_dsp_window_w));
}

// Control board (ADSP-2115 #1): 1K x 24-bit internal program RAM.
void srx_c61_state::dsp1_program_map(address_map &map)
{
	map(0x0000, 0x03ff).ram().share(m_dsp1_pm);
}

void srx_c61_state::dsp1_data_map(address_map &map)
{
	map(0x0000, 0x2fff).ram();                                 // external DM (DWAIT0-2), unused by this board
	map(0x3000, 0x303f).rw(FUNC(srx_c61_state::dsp1_cxd_r), FUNC(srx_c61_state::dsp1_cxd_w));
	map(0x3040, 0x31ff).ram();
	map(0x3200, 0x3200).rw(FUNC(srx_c61_state::dsp1_latch_r), FUNC(srx_c61_state::dsp1_latch_w));
	map(0x3201, 0x33ff).ram();
	map(0x3400, 0x3400).r(FUNC(srx_c61_state::dsp1_adc_r));      // AD7874: CH1..CH4 sequential
	map(0x3401, 0x37ff).ram();
	map(0x3800, 0x39ff).ram();                                 // 512 words internal data RAM
	map(0x3fe0, 0x3ffe).ram();                                 // internal control registers
	map(0x3fff, 0x3fff).rw(FUNC(srx_c61_state::dsp1_syscntl_r), FUNC(srx_c61_state::dsp1_syscntl_w));
}

// Control board (ADSP-2115 #2).
void srx_c61_state::dsp2_program_map(address_map &map)
{
	map(0x0000, 0x03ff).ram().share(m_dsp2_pm);
}

void srx_c61_state::dsp2_data_map(address_map &map)
{
	map(0x0000, 0x2fff).ram();
	map(0x3000, 0x303f).rw(FUNC(srx_c61_state::dsp2_cxd_r), FUNC(srx_c61_state::dsp2_cxd_w));
	map(0x3040, 0x31ff).ram();
	map(0x3200, 0x3200).rw(FUNC(srx_c61_state::dsp2_latch_r), FUNC(srx_c61_state::dsp2_latch_w));
	map(0x3201, 0x33ff).ram();
	map(0x3400, 0x3400).r(FUNC(srx_c61_state::dsp2_adc_r));
	map(0x3401, 0x37ff).ram();
	map(0x3800, 0x39ff).ram();
	map(0x3fe0, 0x3ffe).ram();
	map(0x3fff, 0x3fff).rw(FUNC(srx_c61_state::dsp2_syscntl_r), FUNC(srx_c61_state::dsp2_syscntl_w));
}


// Teach pendant (Z180): 32 KB EPROM at 0, 32 KB RAM at 0x8000.  The EPROM
// image is used only up to 0x205A, the rest is 0xFF.
void srx_c61_state::tp_program_map(address_map &map)
{
	map(0x0000, 0x7fff).rom().region("tp", 0);
	map(0x8000, 0xffff).ram();
}

// Pendant external I/O.  The HD64180 keeps 0x00-0x3F internal (ASCI, timers,
// interrupts), so everything here is decoded off-chip.  Port roles are from the
// firmware (doc/TP_firmware_structure.md section 8.2 and the driver's trace):
//   0x80 W key-matrix column select (bits 0-2) + panel outputs; R status/DIP
//   0x81 R key-matrix rows, active low, for the selected column
//   0x82 W panel latch (LEDs/buzzer); R read-back
//   0x83 W panel init value (0x8A at boot); R read-back
//   0xC0 W HD44780 command; R status (bit 7 = busy, always 0 here)
//   0xC1 W HD44780 data;    R data (unused by the firmware)
void srx_c61_state::tp_io_map(address_map &map)
{
	// MAME's Z180 performs a dummy external access for internal ports so a
	// mixed internal/external decode still sees the bus; swallow it silently.
	map(0x0000, 0x007f).noprw();
	map(0x0080, 0x0080).rw(FUNC(srx_c61_state::tp_port80_r), FUNC(srx_c61_state::tp_port80_w));
	map(0x0081, 0x0081).r(FUNC(srx_c61_state::tp_port81_r));
	map(0x0082, 0x0082).rw(FUNC(srx_c61_state::tp_port82_r), FUNC(srx_c61_state::tp_port82_w));
	map(0x0083, 0x0083).rw(FUNC(srx_c61_state::tp_port83_r), FUNC(srx_c61_state::tp_port83_w));
	map(0x00c0, 0x00c0).rw(FUNC(srx_c61_state::tp_lcd_status_r), FUNC(srx_c61_state::tp_lcd_cmd_w));
	map(0x00c1, 0x00c1).rw(FUNC(srx_c61_state::tp_lcd_data_r), FUNC(srx_c61_state::tp_lcd_data_w));
}


/***************************************************************************
    I/O handlers
***************************************************************************/

uint8_t srx_c61_state::diag_io_r()
{
	return 0;
}

void srx_c61_state::diag_io_w(uint8_t data)
{
	// Port 0x20 is the boot progress / fatal-halt output (plan 7.6).
	logerror("%s: diag port 0x20 = 0x%02X\n", machine().describe_context(), data);
}

void srx_c61_state::blitter_stub_w(offs_t offset, uint8_t data)
{
	// Unidentified write-only latch on the CPU board (boot EPROM writes 2 to
	// 0x24; the SIO2 probe writes the channel number to 0x28).  Stored nowhere
	// on purpose: log only, so a wrong assumption cannot change behaviour.
	logerror("%s: stub latch write <- 0x%02X\n", machine().describe_context(), data);
}


/***************************************************************************
    CPU board peripherals (stage 4)
***************************************************************************/

// ---- 8254 -----------------------------------------------------------------
// The I/O ports are 4 bytes apart, so the chip's counter index is (offset/4).
uint8_t srx_c61_state::pit_r(offs_t offset)
{
	return m_pit->read((offset >> 2) & 3);
}

void srx_c61_state::pit_w(offs_t offset, uint8_t data)
{
	m_pit->write((offset >> 2) & 3, data);
}

void srx_c61_state::pit_out0_w(int state)
{
	// Counter 0 = 100 Hz system tick -> slave PIC IR2 (architecture 4.3).
	if (state && m_tick_out == 0)
		logerror("PIT: 100 Hz system tick running (counter 0 -> slave IR2)\n");
	if (state)
		m_tick_out++;
	m_pic_slave->ir2_w(state);
}

void srx_c61_state::pit_out1_w(int state)
{
	// Counter 1 = user RS-232C (ch 3) baud clock.  Both the TxC and RxC pins
	// of the 8251 are fed from it (architecture report 6.1).  The firmware
	// programs divisor 10 at INIT (307.2 kHz) and changes it for RSSPEED.
	m_uart[2]->write_txc(state);
	m_uart[2]->write_rxc(state);
}

void srx_c61_state::pit_out2_w(int state)
{
	// Counter 2 = teach pendant (ch 1) and PC host (ch 2) baud clock.  The
	// firmware programs divisor 20 -> 153.6 kHz = 9600 baud x16.
	m_uart[0]->write_txc(state);
	m_uart[0]->write_rxc(state);
	m_uart[1]->write_txc(state);
	m_uart[1]->write_rxc(state);
}

// ---- 8251A ----------------------------------------------------------------
uint8_t srx_c61_state::uart_data_r(int ch)
{
	return m_uart[ch]->data_r();
}

void srx_c61_state::uart_data_w(int ch, uint8_t data)
{
	// Bounded trace of transmitted bytes: enough to see the pendant handshake
	// and SRXWIN frames without flooding the log during normal operation.
	if (m_uart_tx_count[ch] < 64)
	{
		logerror("serial ch%d TX: 0x%02X (%c)\n", ch + 1, data,
				(data >= 0x20 && data < 0x7f) ? char(data) : '.');
		m_uart_tx_count[ch]++;
	}
	m_uart[ch]->data_w(data);
}

uint8_t srx_c61_state::uart_status_r(int ch)
{
	return m_uart[ch]->status_r();
}

void srx_c61_state::uart_ctrl_w(int ch, uint8_t data)
{
	if (m_uart_ctrl_count[ch] < 16)
	{
		logerror("serial ch%d control <- 0x%02X\n", ch + 1, data);
		m_uart_ctrl_count[ch]++;
	}

	// MAME's 8251 starts expecting a mode byte, while the firmware performs
	// the standard power-on sequence "00 00 00 40 <mode> <command>".  Feeding
	// all of it to the model makes 0x40 a (synchronous) mode byte and shifts
	// everything, so the command is never accepted.  Drop the leading 00/40
	// preamble once; the first other byte is the real mode byte.
	if (!m_uart_initialized[ch])
	{
		if (data == 0x00 || data == 0x40)
			return;
		m_uart_initialized[ch] = true;
	}

	m_uart[ch]->control_w(data);
}

// The rs232 port device resets with CTS deasserted and its device_reset runs
// after the pseudo-terminal card has driven it low, so the 8251 would stay
// "clear to send = no" and never raise TxRDY.  Re-assert CTS once after the
// reset storm: this model does not implement host flow control.
void srx_c61_state::uart_cts_assert(int unused)
{
	logerror("SRX: serial CTS asserted (no host flow control modelled)\n");
	for (int ch = 0; ch < 3; ch++)
		m_uart[ch]->write_cts(0);
}

void srx_c61_state::uart_txrdy_w(int ch, int state)
{
	if (m_uart_txrdy_count[ch] < 2)
	{
		logerror("serial ch%d TxRDY = %d\n", ch + 1, state);
		m_uart_txrdy_count[ch]++;
	}
	m_pic_slave->set_irq_line(3 + ch, state);
}

void srx_c61_state::uart_rxrdy_w(int ch, int state)
{
	m_pic_master->set_irq_line(1 + ch, state);
}

// CPU ch1 TXD reaches both the optional pty peer and the real pendant's
// ASCI receiver.  The pendant is the normal peer in the whole-system config;
// the pty stays available for monitor/injection work.
void srx_c61_state::uart1_txd_w(int state)
{
	m_rs232[0]->write_txd(state);
	m_tp->rxa0_w(state);
}


/***************************************************************************
    Teach pendant (stage 7)
***************************************************************************/

uint8_t srx_c61_state::tp_port80_r()
{
	// The key scan reads this port, preserves bits 7-3 and writes it back with
	// a new column number.  Bits 7-3 are panel/DIP inputs whose pin-out is not
	// documented; returning the last written value is the least surprising
	// model and keeps the scan loop's own state stable.
	return m_tp_port80;
}

void srx_c61_state::tp_port80_w(uint8_t data)
{
	m_tp_port80 = data;
}

uint8_t srx_c61_state::tp_port81_r()
{
	// Key matrix rows are active low: a cleared bit is a pressed key.
	unsigned const col = m_tp_port80 & 7;
	if (m_tp_keys[col] && m_tp_key_scan_logs++ < 16)
		logerror("SRX TP keypad scan: column %u rows 0x%02X\n", col, uint8_t(~m_tp_keys[col]));
	return uint8_t(~m_tp_keys[col]);
}

uint8_t srx_c61_state::tp_port82_r()
{
	return m_tp_port82;
}

void srx_c61_state::tp_port82_w(uint8_t data)
{
	m_tp_port82 = data;
}

uint8_t srx_c61_state::tp_port83_r()
{
	return m_tp_port83;
}

void srx_c61_state::tp_port83_w(uint8_t data)
{
	m_tp_port83 = data;
}

// HD44780-style 20x4 character LCD.  The firmware uses the standard line
// base addresses 0x00/0x40/0x14/0x54 (see 0x0D2B in the TP image), so map
// DDRAM addresses onto four line-major rows.
int srx_c61_state::tp_lcd_index(uint8_t addr) const
{
	addr &= 0x7f;
	if (addr <= 0x13)
		return addr;
	if (addr >= 0x40 && addr <= 0x53)
		return 20 + (addr - 0x40);
	if (addr >= 0x14 && addr <= 0x33)
		return 40 + (addr - 0x14);
	if (addr >= 0x54 && addr <= 0x73)
		return 60 + (addr - 0x54);
	return -1;
}

void srx_c61_state::tp_display_changed()
{
	for (int line = 0; line < 4; line++)
	{
		char text[21];
		std::memcpy(text, &m_tp_display[line * 20], 20);
		text[20] = '\0';
		if (std::memcmp(text, m_tp_display_last[line], 21) != 0)
		{
			std::memcpy(m_tp_display_last[line], text, 21);
			logerror("SRX TP display L%d: \"%s\"\n", line + 1, text);
		}
	}
}

uint8_t srx_c61_state::tp_lcd_status_r()
{
	// Bit 7 is the busy flag.  The model is always ready; the firmware's only
	// status use is polling this bit before a command/data write.
	return uint8_t(m_tp_cursor & 0x7f);
}

void srx_c61_state::tp_lcd_cmd_w(uint8_t data)
{
	if (data & 0x80)
	{
		m_tp_cursor = data & 0x7f;
		return;
	}

	if (data & 0x40)
		return;                         // set CGRAM address (not modelled)

	if (data & 0x20)
		return;                         // function set (8-bit, lines, font)

	if (data & 0x10)
		return;                         // cursor/display shift

	if (data & 0x08)
	{
		m_tp_display_on = BIT(data, 2);
		return;                         // display/cursor on-off control
	}
	if (data & 0x04)
	{
		m_tp_entry_increment = BIT(data, 1);   // I/D: 1 = increment, 0 = decrement
		return;                         // entry mode set
	}
	if (data & 0x02)
	{
		m_tp_cursor = 0;
		return;                         // return home
	}
	if (data & 0x01)
	{
		std::fill(std::begin(m_tp_display), std::end(m_tp_display), uint8_t(' '));
		m_tp_cursor = 0;
		tp_display_changed();
	}
}

uint8_t srx_c61_state::tp_lcd_data_r()
{
	int const index = tp_lcd_index(m_tp_cursor);
	return (index >= 0) ? m_tp_display[index] : 0x20;
}

void srx_c61_state::tp_lcd_data_w(uint8_t data)
{
	int const index = tp_lcd_index(m_tp_cursor);
	if (index >= 0)
		m_tp_display[index] = data;
	m_tp_cursor = uint8_t(m_tp_cursor + (m_tp_entry_increment ? 1 : -1)) & 0x7f;
	tp_display_changed();
}

// One-shot progress probe: report what the real pendant firmware has in its
// protocol RX buffer 0x8279 (length at +1, command at +2, payload +3..) and
// its status latch 0x8392.  This is the same evidence a serial trace gives,
// without touching the firmware.
void srx_c61_state::tp_status_check(int unused)
{
	address_space &prog = m_tp->space(AS_PROGRAM);
	uint8_t const status = prog.read_byte(0x8392);
	logerror("SRX TP: probe PC=0x%04X buffer %02X %02X %02X %02X %02X %02X %02X status 0x%02X\n",
			m_tp->state_int(Z180_PC),
			prog.read_byte(0x8279), prog.read_byte(0x827a), prog.read_byte(0x827b),
			prog.read_byte(0x827c), prog.read_byte(0x827d), prog.read_byte(0x827e),
			prog.read_byte(0x827f), status);
	if (m_tp->handshake_seen())
		logerror("SRX TP: handshake PASSED between real firmwares (SRX6 received, TP4 sent)\n");
	else
		logerror("SRX TP: no TP4 reply observed by the probe time\n");
}


// ---- 8259A ----------------------------------------------------------------
// Even port = command/status, next even port (stride 4) = data.
uint8_t srx_c61_state::pic_master_r(offs_t offset)
{
	return m_pic_master->read((offset >> 2) & 1);
}

void srx_c61_state::pic_master_w(offs_t offset, uint8_t data)
{
	m_pic_master->write((offset >> 2) & 1, data);
}

uint8_t srx_c61_state::pic_slave_r(offs_t offset)
{
	return m_pic_slave->read((offset >> 2) & 1);
}

void srx_c61_state::pic_slave_w(offs_t offset, uint8_t data)
{
	m_pic_slave->write((offset >> 2) & 1, data);
}

// ---- RTC (MSM6242-like, 16 BCD registers) ---------------------------------
uint8_t srx_c61_state::rtc_r(offs_t offset)
{
	return m_rtc->read((offset >> 2) & 0xf);
}

void srx_c61_state::rtc_w(offs_t offset, uint8_t data)
{
	m_rtc->write((offset >> 2) & 0xf, data);
}

// ---- CPU-board system inputs ----------------------------------------------
// Ports 0x00 and 0x08 are read into the SYST input image at 0x4A08/0x4A09.
// The port pin-out is not documented; the firmware shows that bit 4 of port
// 0x08 means "teach pendant connected" (0x885C / 0x8884 gate the TPCT
// handshake, and 0x8884 returns 1 = disconnected when the bit is clear).
// Bits 0-3 are left at 0 (unknown switches, safe default); flip this model
// once the CPU-board switches/sense lines are identified.
uint8_t srx_c61_state::sys_input0_r()
{
	if (m_sys_input_reads[0]++ < 4)
		logerror("system input port 0x00 read -> 0x00 (unknown, stub)\n");
	return 0x00;
}

uint8_t srx_c61_state::sys_input1_r()
{
	if (m_sys_input_reads[1]++ < 4)
		logerror("system input port 0x08 read -> 0x10 (bit4: pendant connected [I])\n");
	return 0x10;
}

// ---- EEPROM ---------------------------------------------------------------
// Port 0x0C: CPU-board status.  The boot EPROM (0x9D0/0xA90/0xB30) proceeds
// only when bits 0 and 1 are clear.  Bit 6 is the EEPROM write-complete flag:
// the EEPROM driver (0x6C19/0x6C2B) waits one tick after each 32-byte page
// and needs bit 6 set, otherwise it reports 0x7919 (timeout).  Writes land
// instantly in the model, so the chip is always "complete, no error".
// INIT also stores the raw byte at 0x4A0A (0x7F3D) but nothing tests it.
uint8_t srx_c61_state::eeprom_status_r()
{
	return 0x40;
}

void srx_c61_state::eeprom_status_w(uint8_t data)
{
	logerror("%s: EEPROM status port 0x0C <- 0x%02X\n", machine().describe_context(), data);
}

// Default EEPROM contents, used only when no saved nvram/srx_c61/eeprom_nv file
// exists: the "eeprom" ROM region (a real dump, or make_roms.sh's 0xFF blank).
void srx_c61_state::eeprom_nvram_init(nvram_device &nvram, void *data, size_t size)
{
	auto *const dst = static_cast<uint8_t *>(data);
	std::fill_n(dst, size, uint8_t(0xff));
	if (memory_region *eeprom = memregion("eeprom"))
	{
		size_t const bytes = std::min<size_t>(size, eeprom->bytes());
		std::memcpy(dst, eeprom->base(), bytes);
		if (std::any_of(dst, dst + bytes, [](uint8_t b) { return b != 0xff; }))
			logerror("EEPROM: no saved nvram, using the image from the ROM set\n");
		else
			logerror("EEPROM: no saved nvram and no real dump (plan 6.1); blank 0xFF image\n");
	}
}

// ---- PC card --------------------------------------------------------------
uint8_t srx_c61_state::pccard_attr_r()
{
	return m_pccard_attr ? 0x01 : 0x00;     // port 0x4C bit 0 only
}

void srx_c61_state::pccard_attr_w(uint8_t data)
{
	m_pccard_attr = BIT(data, 0);
}

// No card is fitted: an empty slot floats high, which is what the boot
// EPROM's FAT directory scan (0x89E0..0x8A53) checks for (0xFF = no card).
uint8_t srx_c61_state::pccard_r(offs_t offset)
{
	offset <<= 2;                 // dword index -> byte offset
	return 0xff;
}

void srx_c61_state::pccard_w(offs_t offset, uint8_t data)
{
	offset <<= 2;                 // dword index -> byte offset
	if (m_pccard_writes++ < 8)
		logerror("%s: PC card write 0x%06X <- 0x%02X (attribute=%d, no card)\n",
				machine().describe_context(), 0x200000 + offset, data, m_pccard_attr ? 1 : 0);
}

// ---- Slot latches ---------------------------------------------------------
uint8_t srx_c61_state::slot_latch_r(offs_t offset)
{
	unsigned const slot = (offset >> 2) & 7;
	return (slot < 5) ? m_slot_latch[slot] : 0xff;
}

void srx_c61_state::slot_latch_w(offs_t offset, uint8_t data)
{
	unsigned const slot = (offset >> 2) & 7;
	if (slot >= 5)
		return;

	m_slot_latch[slot] = data;
	if (m_slot_latch_writes[slot]++ < 4)
		logerror("%s: slot latch %u <- 0x%02X\n", machine().describe_context(), slot + 1, data);
}

// ---- Flash writes ---------------------------------------------------------
// The 28F400 flash needs command sequences; at this stage they are logged and
// discarded (plan 5.1: "flash writes: log them, ignore at first").  RAM/
// parameter storage is the EEPROM/PC card, not the flash.
void srx_c61_state::flash_w(offs_t offset, uint32_t data, uint32_t mem_mask)
{
	offset <<= 2;                 // dword index -> byte offset
	if (m_flash_writes++ < 32)
		logerror("%s: flash write 0xFFE%05X <- 0x%08X & 0x%08X\n",
				machine().describe_context(), offset, data, mem_mask);
}


/***************************************************************************
    Slot windows: shared SERVO DPRAM, I/O boards, safety panel (stage 5)
***************************************************************************/

uint8_t srx_c61_state::slot_dpram_read_byte(int slot, offs_t offset)
{
	return m_slots[slot].ram[offset & 0xfff];
}

void srx_c61_state::slot_dpram_write_byte(int slot, offs_t offset, uint8_t data)
{
	slot_window &s = m_slots[slot];
	offset &= 0xfff;

	if (offset == 0x0004 && s.handshake_writes < 8)
	{
		s.handshake_writes++;
		logerror("%s: SRX DPRAM slot%d: handshake +0x04 <- 0x%02X\n",
				machine().describe_context(), slot + 1, data);
	}
	if (offset == 0x0010 && s.doorbell_writes < 8)
	{
		s.doorbell_writes++;
		logerror("%s: SRX DPRAM slot%d: doorbell +0x10 <- 0x%02X\n",
				machine().describe_context(), slot + 1, data);
	}

	s.ram[offset] = data;
}

uint8_t srx_c61_state::slot_io_read_byte(int slot, offs_t offset)
{
	slot_window const &s = m_slots[slot];
	unsigned const in_bytes = s.ram[0] & 0x0f;          // info low nibble  = input groups x8 / 8
	unsigned const out_bytes = (s.ram[0] >> 4) & 0x0f;  // info high nibble = output groups x8 / 8

	if (offset == 0)
		return s.ram[0];
	if (offset == 1)
		return s.ram[1];                                // kind 3
	if (offset == 2)
		return s.ram[2];
	if (offset >= 4 && offset < 4 + in_bytes)
		return (m_field_input >> (8 * (offset - 4))) & 0xff;
	if (offset >= 4 + in_bytes && offset < 4 + in_bytes + out_bytes)
		return s.ram[offset];
	return 0xff;
}

void srx_c61_state::slot_io_write_byte(int slot, offs_t offset, uint8_t data)
{
	slot_window &s = m_slots[slot];
	unsigned const in_bytes = s.ram[0] & 0x0f;
	unsigned const out_base = 4 + in_bytes;
	unsigned const out_bytes = (s.ram[0] >> 4) & 0x0f;

	if (offset == 0 || offset == 1)
		return;                                         // info/kind are read-only
	if (offset == 2)
	{
		s.ram[2] = data;                                // SYST writes 0xFF each scan
		return;
	}
	if (offset >= out_base && offset < out_base + out_bytes)
	{
		uint16_t const old = s.field_out;
		unsigned const bit = 8 * (offset - out_base);
		s.ram[offset] = data;
		s.field_out = (s.field_out & ~(uint16_t(0xff) << bit)) | (uint16_t(data) << bit);
		if (old != s.field_out && s.output_writes < 16)
		{
			s.output_writes++;
			logerror("SRX I/O slot%d: output word <- 0x%04X\n", slot + 1, s.field_out);
		}
		return;
	}
	s.ram[offset] = data;
}

void srx_c61_state::slot_cpu_irq(int slot, bool state)
{
	// Architecture report 4.3: slot 1 -> master IR4, slot 2 -> IR5,
	// slot 3 -> IR6, slot 4 -> slave IR0, slot 5 -> slave IR1.
	switch (slot)
	{
	case 0: m_pic_master->set_irq_line(4, state ? ASSERT_LINE : CLEAR_LINE); break;
	case 1: m_pic_master->set_irq_line(5, state ? ASSERT_LINE : CLEAR_LINE); break;
	case 2: m_pic_master->set_irq_line(6, state ? ASSERT_LINE : CLEAR_LINE); break;
	case 3: m_pic_slave->set_irq_line(0, state ? ASSERT_LINE : CLEAR_LINE); break;
	case 4: m_pic_slave->set_irq_line(1, state ? ASSERT_LINE : CLEAR_LINE); break;
	default: break;
	}
}

uint32_t srx_c61_state::slot_r(int slot, offs_t offset, uint32_t mem_mask)
{
	// The 32-bit program space passes dword indices, not byte offsets.
	offset <<= 2;
	uint32_t result = 0;
	bool mailbox_read = false;


	// i486 is little-endian: byte lane 0 is the low byte of `data`.
	for (int lane = 0; lane < 4; lane++)
	{
		uint32_t const mask = 0xffu << (8 * lane);
		if (!(mem_mask & mask))
			continue;

		offs_t const byteaddr = (offset & ~offs_t(3)) + lane;
		uint8_t value = 0xff;

		if (byteaddr <= 0xfff)
		{
			if (slot == 0)
			{
				value = slot_dpram_read_byte(0, byteaddr);
				uint8_t const faulted = servo_status_byte(byteaddr, value);
				if (faulted != value && m_servo_status_logs++ < 16)
					logerror("SRX FAULT: servo axis status +0x%03X read 0x%02X (stored 0x%02X)\n",
							byteaddr, faulted, value);
				value = faulted;
				if (byteaddr == 0xffc)
					mailbox_read = true;
				if (byteaddr == 0x0004 && m_slots[0].handshake_reads < 8)
				{
					m_slots[0].handshake_reads++;
					logerror("%s: SRX DPRAM slot1: handshake +0x04 read -> 0x%02X\n",
							machine().describe_context(), value);
				}
			}
			else if (m_slots[slot].ram[1] == 3)
				value = slot_io_read_byte(slot, byteaddr);
		}

		result |= uint32_t(value) << (8 * lane);
	}

	// Reading the mailbox word acknowledges the SERVO->CPU interrupt; this is
	// exactly what the slot-1 ISR does (mov ax,[0x700FFC]).
	if (mailbox_read && m_slots[0].cpu_irq)
	{
		m_slots[0].cpu_irq = false;
		slot_cpu_irq(0, false);
		if (m_slot_dpram_irq_logs++ < 16)
			logerror("SRX DPRAM slot1: CPU read mailbox 0x%02X, IRQ acknowledged\n",
					m_slots[0].ram[0xffc]);
	}

	return result;
}

void srx_c61_state::slot_w(int slot, offs_t offset, uint32_t data, uint32_t mem_mask)
{
	// The 32-bit program space passes dword indices, not byte offsets.
	offset <<= 2;
	bool mailbox_write = false;

	for (int lane = 0; lane < 4; lane++)
	{
		uint32_t const mask = 0xffu << (8 * lane);
		if (!(mem_mask & mask))
			continue;

		offs_t const byteaddr = (offset & ~offs_t(3)) + lane;
		uint8_t const byte = (data >> (8 * lane)) & 0xff;
		if (byteaddr > 0xfff)
			continue;

		if (slot == 0)
		{
			slot_dpram_write_byte(0, byteaddr, byte);
			if (byteaddr == 0xffc)
				mailbox_write = true;
		}
		else if (m_slots[slot].ram[1] == 3)
			slot_io_write_byte(slot, byteaddr, byte);
	}

	// A CPU write to the mailbox is a CPU->SERVO request.  The real V810
	// interrupt line is unknown (plan 6.4); V810_DPRAM_IRQ documents the
	// guess.  The CPU firmware normally only reads the mailbox.
	if (mailbox_write)
	{
		m_slots[0].servo_irq = true;
		m_servocpu->set_input_line(V810_DPRAM_IRQ, ASSERT_LINE);
		if (m_slot_dpram_irq_logs++ < 16)
			logerror("SRX DPRAM slot1: CPU wrote mailbox 0x%02X -> V810 IRQ %d\n",
					m_slots[0].ram[0xffc], V810_DPRAM_IRQ);
	}
}

// V810 side of slot 1.  The V810 is big-endian, so lane 0 is the high byte.
uint32_t srx_c61_state::servo_dpram_r(offs_t offset, uint32_t mem_mask)
{
	// The 32-bit program space passes dword indices, not byte offsets.
	offset <<= 2;
	uint32_t result = 0;
	bool mailbox_read = false;

	for (int lane = 0; lane < 4; lane++)
	{
		uint32_t const mask = 0xffu << (8 * lane);
		if (!(mem_mask & mask))
			continue;

		offs_t const byteaddr = (offset & ~offs_t(3)) + lane;
		uint8_t value = 0xff;
		if (byteaddr <= 0xfff)
		{
			value = slot_dpram_read_byte(0, byteaddr);
			if (byteaddr == 0xffc)
				mailbox_read = true;
		}
		result |= uint32_t(value) << (8 * lane);
	}


	if (mailbox_read && m_slots[0].servo_irq)
	{
		m_slots[0].servo_irq = false;
		m_servocpu->set_input_line(V810_DPRAM_IRQ, CLEAR_LINE);
		if (m_slot_dpram_irq_logs++ < 16)
			logerror("SRX DPRAM slot1: V810 read mailbox 0x%02X, IRQ acknowledged\n",
					m_slots[0].ram[0xffc]);
	}

	return result;
}

void srx_c61_state::servo_dpram_w(offs_t offset, uint32_t data, uint32_t mem_mask)
{
	// The 32-bit program space passes dword indices, not byte offsets.
	offset <<= 2;
	bool mailbox_write = false;


	for (int lane = 0; lane < 4; lane++)
	{
		uint32_t const mask = 0xffu << (8 * lane);
		if (!(mem_mask & mask))
			continue;

		offs_t const byteaddr = (offset & ~offs_t(3)) + lane;
		uint8_t const byte = (data >> (8 * lane)) & 0xff;
		if (byteaddr > 0xfff)
			continue;

		slot_dpram_write_byte(0, byteaddr, byte);
		if (byteaddr == 0xffc)
			mailbox_write = true;
	}

	// The SERVO writes +0xFFC to interrupt the CPU (value 1/2/4 in the
	// firmware: request / timeout / ack, see doc/servo_dsp_link.md).
	if (mailbox_write)
	{
		m_slots[0].cpu_irq = true;
		slot_cpu_irq(0, true);
		m_slots[0].irq_asserts++;
		if (m_slots[0].irq_asserts <= 16 || (m_slots[0].irq_asserts % 500) == 0)
			logerror("SRX DPRAM slot1: SERVO mailbox 0x%02X -> CPU IRQ (%u)\n",
					m_slots[0].ram[0xffc], m_slots[0].irq_asserts);
	}
}

// ---- Lua safety / field-I/O panel ----------------------------------------
uint8_t srx_c61_state::lua_io_r(offs_t offset)
{
	slot_window const &s = m_slots[0];
	switch (offset)
	{
	case 0: return m_safety_faults;
	case 1: return m_field_input & 0xff;
	case 2: return (m_field_input >> 8) & 0xff;
	case 3: return m_slots[1].field_out & 0xff;
	case 4: return (m_slots[1].field_out >> 8) & 0xff;
	case 5: return s.ram[0xffc];
	case 6: return (s.cpu_irq ? 0x01 : 0x00) | (s.servo_irq ? 0x02 : 0x00);
	case 7: return uint8_t(m_adc_offset);
	case 8: return m_tp_key_col;
	case 9: return m_tp_keys[m_tp_key_col & 7];
	case 10: return m_tp_display_index;
	case 11:
	{
		uint8_t const value = m_tp_display[m_tp_display_index % 80];
		m_tp_display_index = (m_tp_display_index + 1) % 80;
		return value;
	}
	default: return 0;
	}
}

void srx_c61_state::lua_io_w(offs_t offset, uint8_t data)
{
	uint8_t old_faults = m_safety_faults;
	switch (offset)
	{
	case 0: m_safety_faults = data & SAFETY_MASK; break;
	case 1: m_field_input = (m_field_input & 0xff00) | data; break;
	case 2: m_field_input = (m_field_input & 0x00ff) | (uint16_t(data) << 8); break;
	case 7:
		m_adc_offset = int8_t(data);
		if (m_adc_offset_logs++ < 8)
			logerror("SRX FAULT: AD7874 channel offset = %+d\n", int(m_adc_offset));
		break;
	case 8: m_tp_key_col = data & 7; break;
	case 9:
		m_tp_keys[m_tp_key_col & 7] = data;
		logerror("SRX TP keypad: column %u rows 0x%02X (bit set = pressed)\n",
				m_tp_key_col & 7, data);
		break;
	case 10: m_tp_display_index = data % 80; break;
	case 11: m_tp_display_index = data % 80; break;
	default: break;                                     // readback/reserved registers
	}
	if (old_faults != m_safety_faults)
		safety_changed();
}

// Fault bits OR-ed into the CPU-side view of the per-axis servo status dword.
// These are exactly the bits the SVT AMP-status parser 0x3B8B8 tests.
uint32_t srx_c61_state::servo_status_faults() const
{
	uint32_t bits = 0;
	if (m_safety_faults & SAFETY_ESTOP)
		bits |= SERVO_ST_ESTOP;
	if (m_safety_faults & SAFETY_AMPRDY)
		bits |= SERVO_ST_AMPRDY;
	if (m_safety_faults & SAFETY_OVERSPEED)
		bits |= SERVO_ST_OVERSPEED;
	if (m_safety_faults & SAFETY_DRIVER_FAULT)
		bits |= SERVO_ST_AMP_WDT;
	return bits;
}

// slot-1 per-axis blocks live at +0x100*(k+1), k=0..3; the status dword is
// at +0x00.  Apply the fault bits on the CPU side only: the V810 side keeps
// the value its firmware wrote (the model injects an external condition,
// it does not overwrite the board's own status).
uint8_t srx_c61_state::servo_status_byte(offs_t byteaddr, uint8_t stored) const
{
	offs_t const off = byteaddr & 0xfff;
	unsigned const block = off >> 8;
	if (block < 1 || block > 4 || (off & 0xff) > 3)
		return stored;
	uint32_t const bits = servo_status_faults();
	return stored | uint8_t(bits >> (8 * (off & 3)));
}

void srx_c61_state::safety_changed()
{
	uint32_t const bits = servo_status_faults();
	if (m_safety_logs++ < 32)
		logerror("SRX SAFETY: faults 0x%02X (estop=%d dss_off=%d amprdy=%d overspeed=%d driver=%d) -> servo status bits 0x%05X\n",
				m_safety_faults,
				(m_safety_faults & SAFETY_ESTOP) ? 1 : 0,
				(m_safety_faults & SAFETY_DSS_OFF) ? 1 : 0,
				(m_safety_faults & SAFETY_AMPRDY) ? 1 : 0,
				(m_safety_faults & SAFETY_OVERSPEED) ? 1 : 0,
				(m_safety_faults & SAFETY_DRIVER_FAULT) ? 1 : 0,
				bits);

	// DSS is a real system-input bit: keep bit 6 of the field-input word in
	// step with the switch, so the SYST I/O scan (0x108FC) writes it into
	// the firmware's input image 0x62B8, where app_10C5C(7) reads it.
	if (m_safety_faults & SAFETY_DSS_OFF)
		m_field_input &= ~uint16_t(0x0040);
	else
		m_field_input |= 0x0040;

	// The DSP FLAG_IN input is the amplifier-ready/safety level.  Keep the
	// default (all clear) behaviour of stage 2/3; a fault drops it.
	bool const clear = (m_safety_faults == 0);
	dsp_set_flag_in(0, clear ? 1 : 0);
	dsp_set_flag_in(1, clear ? 1 : 0);

	// Trace the error path this switch feeds, so a run shows the cause even
	// when the EEPROM blocker keeps the SVT/error task from reaching it.
	if (m_safety_faults & SAFETY_DSS_OFF)
		logerror("SRX FAULT: DSS off -> system-input 0x62B8 bit 6 = 0; "
				"app_3BD28 (0x3BD28) would request E401 (code 0x191 at 0x3BE1B)\n");
	if (m_safety_faults & SAFETY_OVERSPEED)
		logerror("SRX FAULT: SPD over-speed -> servo status 0x4000; "
				"SVT AMP parser 0x3B8B8 would request E400 (code 0x190 at 0x3BAF5)\n");
	if (m_safety_faults & SAFETY_AMPRDY)
		logerror("SRX FAULT: AMPRDY fail -> servo status 0x80000; "
				"parser 0x3B8B8 would request E341 (code 0x155)\n");
	if (m_safety_faults & SAFETY_DRIVER_FAULT)
		logerror("SRX FAULT: driver fault -> servo status 0x400; "
				"parser 0x3B8B8 would request E340 (code 0x154)\n");
	if (m_safety_faults & SAFETY_ESTOP)
		logerror("SRX FAULT: E-stop -> servo status 0x1000; "
				"parser 0x3B8B8 would request E300 (code 0x12C)\n");
}


// Stage 1: the SERVO 0x30000x block is the baud/SCI setup (observed command
// values 0x30/0x74/0xB4 and a 16-bit divisor).  The monitor does not emit its
// banner standalone: it idles polling slot DPRAM 0x200004 for the host
// handshake, which stage 5 now supplies from the CPU side.  The SERVO-board
// safety inputs themselves are not identified yet (plan 5.7/6.12): the
// V810 only sees the safety chain through the DSP status/FLAG_IN path.
uint32_t srx_c61_state::servo_console_r(offs_t offset)
{
	offset <<= 2;                 // dword index -> byte offset
	return 0;
}

void srx_c61_state::servo_console_w(offs_t offset, uint32_t data, uint32_t mem_mask)
{
	offset <<= 2;                 // dword index -> byte offset
	for (int shift = 0; shift < 32; shift += 8)
	{
		uint8_t const byte = (data >> shift) & 0xff;
		uint32_t const m = (mem_mask >> shift) & 0xff;
		if (m && byte >= 0x20 && byte < 0x7f)
			logerror("SERVO console: '%c' (0x%02x) -> reg 0x30000%x\n", byte, byte, offset + (shift / 8));
	}
	logerror("%s: SERVO reg 0x30000%x <- 0x%08x & 0x%08x\n", machine().describe_context(), offset, data, mem_mask);
}


/***************************************************************************
    SERVO <-> Control board windows (stage 3)
***************************************************************************/

// The V810 side sees DSP DM $3000-$303F as 64 16-bit words at byte 2n.
// Both accesses operate on the same cxd8501r_model registers as the DSP
// data maps, so the DSP firmware's acknowledge (writing 0 to $3000) is
// immediately visible to the V810 polling the command word.
uint32_t srx_c61_state::servo_dsp_window_r(offs_t offset, uint32_t mem_mask)
{
	// The 32-bit program space passes dword indices, not byte offsets.
	offset = (offset << 2) & 0x00ff;
	uint32_t result = 0;

	for (int lane = 0; lane < 4; lane++)
	{
		uint32_t const mask = 0xffu << (8 * lane);
		if (!(mem_mask & mask))
			continue;

		offs_t const byteaddr = (offset & ~offs_t(3)) + lane;
		int const which = (byteaddr & 0x80) ? 1 : 0;
		offs_t const reg = (byteaddr & 0x7f) >> 1;
		uint16_t const value = dsp_cxd_r(which, reg);
		uint8_t const byte = (byteaddr & 1) ? uint8_t(value >> 8) : uint8_t(value & 0xff);
		result |= uint32_t(byte) << (8 * lane);
	}

	return result;
}

void srx_c61_state::servo_dsp_window_w(offs_t offset, uint32_t data, uint32_t mem_mask)
{
	// The 32-bit program space passes dword indices, not byte offsets.
	offset = (offset << 2) & 0x00ff;

	// Collect the touched registers first, then run the normal CXD8501R write
	// handler once per register so its side effects (mailbox ack logging,
	// $3021 W1C, $3025 ADC start) behave exactly as on the DSP bus.
	int n = 0;
	int touched_which[4];
	offs_t touched_reg[4];
	uint16_t touched_value[4];

	for (int lane = 0; lane < 4; lane++)
	{
		uint32_t const mask = 0xffu << (8 * lane);
		if (!(mem_mask & mask))
			continue;

		offs_t const byteaddr = (offset & ~offs_t(3)) + lane;
		int const which = (byteaddr & 0x80) ? 1 : 0;
		offs_t const reg = (byteaddr & 0x7f) >> 1;
		uint8_t const byte = (data >> (8 * lane)) & 0xff;

		int entry = -1;
		for (int i = 0; i < n; i++)
		{
			if (touched_which[i] == which && touched_reg[i] == reg)
			{
				entry = i;
				break;
			}
		}
		if (entry < 0)
		{
			entry = n++;
			touched_which[entry] = which;
			touched_reg[entry] = reg;
			touched_value[entry] = m_cxd[which].regs[reg];
		}

		if (byteaddr & 1)
			touched_value[entry] = (touched_value[entry] & 0x00ff) | (uint16_t(byte) << 8);
		else
			touched_value[entry] = (touched_value[entry] & 0xff00) | byte;
	}

	for (int i = 0; i < n; i++)
		dsp_cxd_w(touched_which[i], touched_reg[i], touched_value[i]);
}


/***************************************************************************
    Control board (stage 2)
***************************************************************************/

void srx_c61_state::dsp_set_line(int which, int line, int state)
{
	adsp2115_device &dsp = which ? *m_dsp2 : *m_dsp1;
	dsp.set_input_line(line, state);
}

// The ADSP-21xx core has no external FLAG_IN input line (only the register
// state), so the driver drives the state directly.  FLAG_IN is the safety
// chain / amplifier-ready input (plan section 5.4): with it asserted the DSP
// accepts the mode commands and actually enables a motor.  Default = "all
// clear", which is what a fault-injection switch would deassert later.
void srx_c61_state::dsp_set_flag_in(int which, int level)
{
	adsp2115_device &dsp = which ? *m_dsp2 : *m_dsp1;
	device_state_interface *iface = nullptr;
	if (dsp.interface(iface) && iface)
	{
		iface->set_state_int(ADSP2100_FLAGIN, level ? 1 : 0);
		if (!m_flagin_logged[which])
		{
			m_flagin_logged[which] = true;
			device_state_entry const *entry = iface->state_find_entry(ADSP2100_FLAGIN);
			logerror("DSP%d FLAG_IN modelled as %d (safety chain all clear)\n",
					which + 1, entry ? int(entry->value()) : -1);
		}
	}
}

void srx_c61_state::dsp_boot_page(int which, int page)
{
	if (page < 0 || page > 2)
	{
		logerror("DSP%d BFORCE: unsupported boot page %d\n", which + 1, page);
		return;
	}

	memory_region *region = which ? memregion("dsp2") : memregion("dsp1");
	offs_t const offs = offs_t(page) * 0x2000;
	if (!region || offs + 4 > region->bytes())
	{
		logerror("DSP%d BFORCE: page %d outside boot ROM\n", which + 1, page);
		return;
	}

	uint8_t *src = region->base() + offs;
	if (which)
	{
		m_dsp2->load_boot_data(src, m_dsp2_pm);
		m_page1_active[1] = (page == 1);
		m_dsp2->pulse_input_line(INPUT_LINE_RESET, attotime::zero);
	}
	else
	{
		m_dsp1->load_boot_data(src, m_dsp1_pm);
		m_page1_active[0] = (page == 1);
		m_dsp1->pulse_input_line(INPUT_LINE_RESET, attotime::zero);
	}

	logerror("DSP%d BFORCE -> boot page %d (%d words)\n", which + 1, page, (src[3] + 1) * 8);

	// A fresh reset does not clear the DAG registers in the core, which is
	// exactly what page 1 expects (M0..M7 from page 0).
}

// CXD8501R register file.  Offsets are relative to DM 0x3000.
uint16_t srx_c61_state::dsp_cxd_r(int which, offs_t offset)
{
	offset &= 0x3f;
	uint16_t value = m_cxd[which].regs[offset];

	// Stage 5 fault injection: the mapping of the safety signals onto the
	// CXD8501R status word is not decoded yet (plan 5.4/5.7), so only add
	// the bits when a fault is active.  All-clear returns the stored value
	// unchanged, which keeps the stage-2/3 command handshake intact.
	if (m_safety_faults != 0)
	{
		if (offset == 0x0021)
			value |= 0x0200;                            // [H] amplifier fault
		else if (offset == 0x003f)
			value |= 0x003c;                            // [H] status bits 2-5 (plan 5.4)
	}
	return value;
}

void srx_c61_state::dsp_cxd_w(int which, offs_t offset, uint16_t data)
{
	offset &= 0x3f;
	cxd8501r_model &cxd = m_cxd[which];
	uint16_t const old = cxd.regs[offset];
	cxd.regs[offset] = data;

	// $3021 bit 7 is a write-1-to-clear status/acknowledge bit.  Page 1's IRQ2
	// handler strobes $0080 and then the main loop expects ($3021 & $0380) == 0
	// before it acknowledges a host command.
	if (offset == 0x0021 && (data & 0x0080))
		cxd.regs[offset] &= ~0x0080;

	if (offset == 0x0000)
	{
		// Host mailbox command: the DSP writes 0 to acknowledge.
		if (data != 0)
			logerror("DSP%d mailbox <- %04X\n", which + 1, data);
		else if (old != 0)
			logerror("DSP%d mailbox ACK (command %04X)\n", which + 1, old);
		return;
	}

	dsp_cxd_log(which, offset, data);

	// $3025 write $0080 starts an AD7874 conversion; IRQ1 follows after the
	// conversion time (guessed 5 us).
	if (offset == 0x0025 && data == 0x0080)
		m_adc_timer[which]->adjust(attotime::from_usec(5), which);

	// $3026/$3027 and $302A/$302B are 24-bit position counters, the PWM
	// registers $3033-$303C feed the plant.  The registers are stored as-is;
	// plant coupling is stage 6.
}

void srx_c61_state::dsp_cxd_log(int which, offs_t offset, uint16_t data)
{
	// Mailbox words and the PWM compares are accessed every control cycle;
	// log only the first few accesses per register to keep the trace useful.
	bool const interesting = (offset >= 0x0021 && offset <= 0x0025) ||
							 offset == 0x0029 || offset == 0x002d ||
							 offset == 0x002f || offset == 0x0030 ||
							 offset == 0x0031 || offset == 0x0033 ||
							 offset == 0x003f;
	if (!interesting || m_cxd_log_count[which][offset] >= 8)
		return;

	m_cxd_log_count[which][offset]++;
	logerror("DSP%d CXD $30%02X <- %04X\n", which + 1, offset, data);
}

uint16_t srx_c61_state::dsp_adc_r(int which)
{
	// AD7874: four consecutive reads return CH1..CH4.  Values are a stub (the
	// plant model supplies real phase currents in stage 6).
	unsigned &index = m_adc_index[which];
	int const raw = int(m_adc[which][index]) + int(m_adc_offset);
	uint16_t const result = uint16_t(std::clamp(raw, 0, 0xffff));
	index = (index + 1) & 3;
	return result;
}

uint16_t srx_c61_state::dsp_latch_r(int which)
{
	return m_outlatch[which];
}

void srx_c61_state::dsp_latch_w(int which, uint16_t data)
{
	uint16_t const old = m_outlatch[which];
	m_outlatch[which] = data;

	if ((old ^ data) & 0x0080)
	{
		// Bit 7 is the heartbeat LED; page 1 uses IRQ2 to toggle it.
		if (m_page1_active[which])
			logerror("DSP%d heartbeat bit 7 = %d\n", which + 1, (data >> 7) & 1);
	}
	if ((old ^ data) & 0x0001)
		logerror("DSP%d ABS mux select = motor %c\n", which + 1, (data & 1) ? 'B' : 'A');
}

uint16_t srx_c61_state::dsp_syscntl_r(int which)
{
	return m_syscntl[which];
}

void srx_c61_state::dsp_syscntl_w(int which, uint16_t data)
{
	m_syscntl[which] = data;

	// Bit 9 = BFORCE: reload PM from boot page BPAGE (bits 6-8) and reset the
	// core.  Page 0 uses $0258 to enter page 1 and page 1 uses $0298 for page 2.
	if (BIT(data, 9))
	{
		int const page = (data >> 6) & 7;
		m_syscntl[which] = data & ~0x0200;
		dsp_boot_page(which, page);
	}
}

void srx_c61_state::dsp_irq1_tick(int which)
{
	m_adc_index[which] = 0;             // new conversion: reads start at CH1
	dsp_set_line(which, ADSP2115_IRQ1, ASSERT_LINE);
	m_irq_clear_timer[which]->adjust(attotime::from_usec(2), which);
}

void srx_c61_state::dsp_irq2_tick(int which)
{
	// Re-assert the safety-chain input every supervision tick: a core reset
	// (BFORCE) clears the FLAG_IN register, and this is the input the IRQ2
	// handler evaluates before it latches the requested motor mode.
	dsp_set_flag_in(which, (m_safety_faults == 0) ? 1 : 0);
	dsp_set_line(which, ADSP2115_IRQ2, ASSERT_LINE);
	m_irq_clear_timer[which]->adjust(attotime::from_usec(2), which);
}

void srx_c61_state::dsp_irq_clear(int which)
{
	dsp_set_line(which, ADSP2115_IRQ1, CLEAR_LINE);
	dsp_set_line(which, ADSP2115_IRQ2, CLEAR_LINE);
}

void srx_c61_state::dsp_adc_done(int which)
{
	m_adc_index[which] = 0;
	dsp_set_line(which, ADSP2115_IRQ1, ASSERT_LINE);
	m_irq_clear_timer[which]->adjust(attotime::from_usec(2), which);
}

void srx_c61_state::dsp_selftest(int step)
{
	// Stage-3 acceptance aid: the SERVO monitor is still gated on the DPRAM
	// host handshake (stage 1), so drive the V810 window handlers directly,
	// exactly as the V810 firmware would: command word at window offset 0,
	// then poll it until the DSP writes 0 back.
	static const uint16_t commands[] = { 0x8001, 0x8002, 0x8000 };   // connect, servo on, servo off
	static const char *const names[] = { "CONNECT 0x8001", "SERVO ON 0x8002", "SERVO OFF 0x8000" };
	static constexpr int window[2] = { 0x00, 0x80 };                 // DSP 1 / DSP 2

	if (step > 0)
	{
		int const prev = step - 1;
		for (int which = 0; which < 2; which++)
		{
			uint16_t const ack = uint16_t(servo_dsp_window_r(window[which], 0x0000ffff) & 0xffff);
			logerror("Stage-3 window self-test: DSP%d %s ack=%04X (%s)\n",
					which + 1, names[prev], ack, ack == 0 ? "ACKED" : "NOT ACKED");
		}
	}

	if (step < int(std::size(commands)))
	{
		for (int which = 0; which < 2; which++)
		{
			logerror("Stage-3 window self-test: DSP%d <- %s via window 0x40%04X\n",
					which + 1, names[step], 0x0000 + window[which]);
			servo_dsp_window_w(window[which], uint32_t(commands[step]), 0x0000ffff);
		}
		m_selftest_timer->adjust(attotime::from_msec(200), step + 1);
	}
}


/***************************************************************************
    Machine config
***************************************************************************/

void srx_c61_state::srx_c61(machine_config &config)
{
	// i486DX2: 50 MHz internal, 25 MHz bus (plan 4).  I486 type (no DX2 variant in MAME).
	I486(config, m_maincpu, 50'000'000);
	m_maincpu->set_addrmap(AS_PROGRAM, &srx_c61_state::maincpu_map);
	m_maincpu->set_addrmap(AS_IO, &srx_c61_state::maincpu_io_map);

	// NEC uPD70732 (V810) @ 25 MHz.
	V810(config, m_servocpu, 25'000'000);
	m_servocpu->set_addrmap(AS_PROGRAM, &srx_c61_state::servocpu_map);

	// ADSP-2115 x2 (KP-66 speed grade; exact clock to measure, plan 4).
	ADSP2115(config, m_dsp1, 16'000'000);
	m_dsp1->set_addrmap(AS_PROGRAM, &srx_c61_state::dsp1_program_map);
	m_dsp1->set_addrmap(AS_DATA, &srx_c61_state::dsp1_data_map);

	ADSP2115(config, m_dsp2, 16'000'000);
	m_dsp2->set_addrmap(AS_PROGRAM, &srx_c61_state::dsp2_program_map);
	m_dsp2->set_addrmap(AS_DATA, &srx_c61_state::dsp2_data_map);

	// ---- stage 7: teach pendant ----
	// HD64180/Z180 at 6.144 MHz (a common value; the real crystal is not
	// measured, see the srx_tp_z180_device note and emulator plan 5.8).
	SRX_TP_Z180(config, m_tp, 6'144'000);
	m_tp->set_addrmap(AS_PROGRAM, &srx_c61_state::tp_program_map);
	m_tp->set_addrmap(AS_IO, &srx_c61_state::tp_io_map);

	// ---- stage 4: CPU-board peripherals ----

	// 8254: 3.072 MHz input (architecture report 6.1).  Counter 0 = 100 Hz
	// system tick (divisor 0x7A12), counter 1/2 = serial baud clocks.
	PIT8254(config, m_pit, 3'072'000);
	m_pit->set_clk<0>(3'072'000);
	m_pit->set_clk<1>(3'072'000);
	m_pit->set_clk<2>(3'072'000);
	m_pit->out_handler<0>().set(FUNC(srx_c61_state::pit_out0_w));
	m_pit->out_handler<1>().set(FUNC(srx_c61_state::pit_out1_w));
	m_pit->out_handler<2>().set(FUNC(srx_c61_state::pit_out2_w));

	// 8259A pair, cascaded on master IR7, vectors 0x20 / 0x28.
	PIC8259(config, m_pic_master, 0);
	m_pic_master->out_int_callback().set_inputline(m_maincpu, 0);
	m_pic_master->in_sp_callback().set_constant(1);
	m_pic_master->read_slave_ack_callback().set(m_pic_slave, FUNC(pic8259_device::acknowledge));

	PIC8259(config, m_pic_slave, 0);
	m_pic_slave->out_int_callback().set(m_pic_master, FUNC(pic8259_device::ir7_w));
	m_pic_slave->in_sp_callback().set_constant(0);

	m_maincpu->set_irq_acknowledge_callback(m_pic_master, FUNC(pic8259_device::inta_cb));

	// Three 8251A USARTs.  External TxC/RxC from the 8254, so clock = 0.
	for (int ch = 0; ch < 3; ch++)
	{
		I8251(config, m_uart[ch], 0);

		RS232_PORT(config, m_rs232[ch], default_rs232_devices, "pty");
		if (ch == 0)
			m_uart[ch]->txd_handler().set(FUNC(srx_c61_state::uart1_txd_w));
		else
			m_uart[ch]->txd_handler().set(m_rs232[ch], FUNC(rs232_port_device::write_txd));
		m_uart[ch]->dtr_handler().set(m_rs232[ch], FUNC(rs232_port_device::write_dtr));
		m_uart[ch]->rts_handler().set(m_rs232[ch], FUNC(rs232_port_device::write_rts));
		m_rs232[ch]->rxd_handler().set(m_uart[ch], FUNC(i8251_device::write_rxd));
		m_rs232[ch]->dsr_handler().set(m_uart[ch], FUNC(i8251_device::write_dsr));
		m_rs232[ch]->cts_handler().set(m_uart[ch], FUNC(i8251_device::write_cts));
	}

	// Pendant ASCI channel 0 transmit -> CPU ch1 8251A receive.  No CTS or DCD
	// handshake is modelled on the pendant link; the ASCI receiver is enabled
	// by the firmware itself (CNTLA0 = 0x65, 8N2).
	m_tp->txa0_wr_callback().set(m_uart[0], FUNC(i8251_device::write_rxd));

	// IRQ wiring from the serial channels (architecture report 4.3):
	// RX = master IR1/IR2/IR3, TX = slave IR3/IR4/IR5.
	m_uart[0]->rxrdy_handler().set(FUNC(srx_c61_state::uart1_rxrdy_w));
	m_uart[1]->rxrdy_handler().set(FUNC(srx_c61_state::uart2_rxrdy_w));
	m_uart[2]->rxrdy_handler().set(FUNC(srx_c61_state::uart3_rxrdy_w));
	m_uart[0]->txrdy_handler().set(FUNC(srx_c61_state::uart1_txrdy_w));
	m_uart[1]->txrdy_handler().set(FUNC(srx_c61_state::uart2_txrdy_w));
	m_uart[2]->txrdy_handler().set(FUNC(srx_c61_state::uart3_txrdy_w));

	// RTC: MSM6242-like part, 16 BCD registers on ports 0x60..0x9C.
	MSM6242(config, m_rtc, 32.768_kHz_XTAL);

	// 8 KB parameter EEPROM (U50 HN58C66 / U26 HN58V66A): persists across runs.
	NVRAM(config, m_eeprom_nv, nvram_device::DEFAULT_CUSTOM);
	m_eeprom_nv->set_custom_handler(FUNC(srx_c61_state::eeprom_nvram_init));
}


/***************************************************************************
    Machine start / reset
***************************************************************************/

void srx_c61_state::machine_start()
{
	for (int i = 0; i < 2; i++)
	{
		m_cxd[i].reset();
		std::fill(std::begin(m_adc[i]), std::end(m_adc[i]), 0);
		m_adc_index[i] = 0;
		m_outlatch[i] = 0;
		m_syscntl[i] = 0;
		m_page1_active[i] = false;
		m_flagin_logged[i] = false;
		std::fill(std::begin(m_cxd_log_count[i]), std::end(m_cxd_log_count[i]), 0);

		m_irq1_timer[i] = timer_alloc(FUNC(srx_c61_state::dsp_irq1_tick), this);
		m_irq2_timer[i] = timer_alloc(FUNC(srx_c61_state::dsp_irq2_tick), this);
		m_irq_clear_timer[i] = timer_alloc(FUNC(srx_c61_state::dsp_irq_clear), this);
		m_adc_timer[i] = timer_alloc(FUNC(srx_c61_state::dsp_adc_done), this);
	}
	m_selftest_timer = timer_alloc(FUNC(srx_c61_state::dsp_selftest), this);

	// Load boot page 0 (loader/initialiser) of each DSP.  Page 0 reboots into
	// page 1 by writing SYSCNTL, which our handler routes through BFORCE.
	m_dsp1->load_boot_data(memregion("dsp1")->base(), m_dsp1_pm);
	m_dsp2->load_boot_data(memregion("dsp2")->base(), m_dsp2_pm);

	// Safety chain "all clear" (see dsp_set_flag_in); re-applied on every
	// supervision tick because BFORCE resets the core.
	dsp_set_flag_in(0, 1);
	dsp_set_flag_in(1, 1);

	// Guessed periodic sources (see the note at the top of the file).
	m_irq1_timer[0]->adjust(attotime::from_hz(DSP_IRQ1_HZ), 0, attotime::from_hz(DSP_IRQ1_HZ));
	m_irq1_timer[1]->adjust(attotime::from_hz(DSP_IRQ1_HZ), 1, attotime::from_hz(DSP_IRQ1_HZ));
	m_irq2_timer[0]->adjust(attotime::from_hz(DSP_IRQ2_HZ), 0, attotime::from_hz(DSP_IRQ2_HZ));
	m_irq2_timer[1]->adjust(attotime::from_hz(DSP_IRQ2_HZ), 1, attotime::from_hz(DSP_IRQ2_HZ));

	// ---- stage 5: slot windows, I/O boards, safety panel ----
	std::fill(std::begin(m_slot_latch), std::end(m_slot_latch), 0);
	std::fill(std::begin(m_slot_latch_writes), std::end(m_slot_latch_writes), 0);
	m_pccard_attr = false;
	m_flash_writes = 0;
	m_pccard_writes = 0;
	m_tick_out = 0;
	m_cts_timer = timer_alloc(FUNC(srx_c61_state::uart_cts_assert), this);
	m_cts_timer->adjust(attotime::from_msec(1));
	std::fill(std::begin(m_uart_tx_count), std::end(m_uart_tx_count), 0);
	std::fill(std::begin(m_uart_ctrl_count), std::end(m_uart_ctrl_count), 0);
	std::fill(std::begin(m_uart_txrdy_count), std::end(m_uart_txrdy_count), 0);
	std::fill(std::begin(m_uart_initialized), std::end(m_uart_initialized), false);
	std::fill(std::begin(m_sys_input_reads), std::end(m_sys_input_reads), 0);

	// Slot DPRAM header bytes (plan 5.2, architecture report 8.4): info at
	// +0, kind at +1.  Population guess of the owner's unit: one SERVO board
	// (kind 1) and two I/O boards (kind 3) in slots 1-3, slots 4/5 empty.
	// Slot order is unconfirmed (plan 6.13).  The V810 writes its own header
	// at boot; these values are the CPU-side fallback so discovery never sees
	// an empty slot 1 before the SERVO has started.
	for (int i = 0; i < 5; i++)
	{
		slot_window &s = m_slots[i];
		std::fill(std::begin(s.ram), std::end(s.ram), 0);
		s.mailbox = 0;
		s.cpu_irq = false;
		s.servo_irq = false;
		s.field_out = 0;
		s.irq_asserts = 0;
		s.handshake_writes = 0;
		s.handshake_reads = 0;
		s.doorbell_writes = 0;
		s.output_writes = 0;
	}

	m_slots[0].ram[0x001] = 0x01;           // slot 1: servo board
	m_slots[1].ram[0x000] = 0x22;           // slot 2: I/O board, 2 in / 2 out groups
	m_slots[1].ram[0x001] = 0x03;
	m_slots[2].ram[0x000] = 0x22;           // slot 3: I/O board
	m_slots[2].ram[0x001] = 0x03;
	m_slots[3].ram[0x001] = 0x00;           // slot 4: empty
	m_slots[4].ram[0x001] = 0x00;           // slot 5: empty

	// 8-byte ROM version string read from slot 1 at +0xF00 by 0x897C for the
	// "SRV ROM" screen.  The V810 copies the real string here at boot; this
	// is only a fallback for the pre-SERVO window.
	static constexpr char servo_version[8] = { 'S','R','X','6','-','S','V',0 };
	std::memcpy(&m_slots[0].ram[0xf00], servo_version, sizeof(servo_version));

	// ---- stage 7: teach pendant ----
	std::fill(std::begin(m_tp_display), std::end(m_tp_display), uint8_t(' '));
	for (int line = 0; line < 4; line++)
	{
		std::memset(m_tp_display_last[line], ' ', 20);
		m_tp_display_last[line][20] = '\0';
	}
	m_tp_cursor = 0;
	m_tp_entry_increment = true;
	m_tp_display_on = false;
	m_tp_port80 = 0x20;                 // value left by sub_695 after init
	m_tp_port82 = 0;
	m_tp_port83 = 0x8a;
	std::fill(std::begin(m_tp_keys), std::end(m_tp_keys), uint8_t(0));
	m_tp_key_col = 0;
	m_tp_display_index = 0;
	m_tp_key_scan_logs = 0;
	logerror("SRX TP: Z180 running the pendant EPROM; ASCI ch0 <-> CPU ch1 8251A\n");
	m_tp_status_timer = timer_alloc(FUNC(srx_c61_state::tp_status_check), this);
	m_tp_status_timer->adjust(attotime::from_msec(3500));

	// Safety chain defaults: everything clear.  Field input word 0 bit 6 is
	// the DSS input (1 = DSS on; E401 fires when it is 0, see error_401 doc).
	m_safety_faults = 0;
	m_field_input = 0x0040;             // raw field inputs, bit 6 = DSS on
	m_adc_offset = 0;
	m_safety_logs = 0;
	m_slot_dpram_irq_logs = 0;
	m_adc_offset_logs = 0;
	m_servo_status_logs = 0;
	safety_changed();

	// EEPROM: the 8 KB window is the nvram device's storage.  MAME loads the
	// saved image (or calls eeprom_nvram_init) after machine_start and saves
	// it on exit.  The byte order is the address order on a little-endian host.
	m_eeprom_nv->set_base(&m_eeprom_ram[0], 0x2000);

	// The default peer of every rs232 port is a pseudo terminal; print its
	// slave device so an external program can connect to it.
	for (int ch = 0; ch < 3; ch++)
	{
		if (auto *pty = dynamic_cast<device_pty_interface *>(m_rs232[ch]->get_card_device()))
		{
			if (pty->is_open())
				osd_printf_info("SRX: serial ch%d (%s) pty: %s\n", ch + 1,
						ch == 0 ? "teach pendant" : (ch == 1 ? "PC host" : "user RS-232C"),
						pty->slave_name());
		}
	}

#if SRX_STAGE3_SELFTEST
	m_selftest_timer->adjust(attotime::from_msec(500), 0);
#endif
}


/***************************************************************************
    ROM definitions
***************************************************************************/

ROM_START(srx_c61)
	ROM_REGION32_LE(0x100000, "maincpu", 0)
	ROM_LOAD("rom1_c.bin", 0x000000, 0x100000, CRC(f06c5759) SHA1(e1ee28f921d3bb221983ac2bac85bfed75e17c46))

	ROM_REGION32_LE(0x008000, "boot", 0)
	ROM_LOAD("u23_eprom.bin", 0x000000, 0x008000, CRC(cf32cc38) SHA1(4b520a9b555016d9f0e61f3c1865341746817735))

	ROM_REGION32_LE(0x040000, "servocpu", 0)
	ROM_LOAD("rom_servo.bin", 0x000000, 0x040000, CRC(9ae87903) SHA1(d1441dcc17ac63344ff5eee949e0bb874fa45e32))

	ROM_REGION(0x010000, "dsp1", 0)
	ROM_LOAD("u7_dsp.bin", 0x000000, 0x010000, CRC(5aa49dc6) SHA1(d6262065093f3780789fdfb90606c27e8b1c31dc))

	ROM_REGION(0x010000, "dsp2", 0)
	ROM_LOAD("u18_dsp.bin", 0x000000, 0x010000, CRC(5aa49dc6) SHA1(d6262065093f3780789fdfb90606c27e8b1c31dc))

	// 32 KB teach-pendant EPROM (M27C256B, socket IC6, HD64180).  Only the
	// first 0x205A bytes are used; the rest is 0xFF.  CRC/SHA1 of the real dump.
	ROM_REGION(0x008000, "tp", 0)
	ROM_LOAD("tp.bin", 0x000000, 0x008000, CRC(c380d24b) SHA1(374a62fb1affeb481f593c7d43a158ef21be9663))

	// 8 KB CPU-board EEPROM.  The real contents are NOT available (plan 6.1,
	// P1 blocker).  make_roms.sh creates a blank (0xFF) "eeprom.bin" only if
	// one is not already present, so a real dump can be dropped into the ROM
	// set: MAME then reports a hash mismatch but still loads it -- update the
	// CRC/SHA1 below once a real dump exists.
	ROM_REGION(0x002000, "eeprom", 0)
	ROM_LOAD("eeprom.bin", 0x000000, 0x002000, CRC(b4293435) SHA1(5e2b96c19c4f5c63a5afa2de504d29fe64a4c908))
ROM_END

} // anonymous namespace


//    YEAR  NAME     PARENT  MACHINE  INPUT  CLASS          INIT       MONITOR  COMPANY  FULLNAME                          FLAGS
GAME(1995, srx_c61, 0,      srx_c61, 0,     srx_c61_state, empty_init, ROT0,   "Sony",  "SRX-611 SCARA Robot Controller",  MACHINE_NOT_WORKING | MACHINE_NO_SOUND)
