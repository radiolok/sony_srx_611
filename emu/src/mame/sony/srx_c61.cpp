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

    Stage 2 (this file): Control board models.
      - boot page 0 is loaded by machine_start(); BFORCE writes to SYSCNTL
        (DM 0x3FFF bit 9) reload BPAGE (bits 6-8) and reset the core while
        keeping the DAG registers, exactly like the real chip;
      - CXD8501R: 64 shared words at DM 0x3000-0x303F (mailbox, control,
        24-bit position counters, driver IDs, PWM);
      - AD7874: four sequential reads at DM 0x3400;
      - IRQ1 (ADC end-of-conversion) and IRQ2 (supervision tick) are driven
        by timers at guessed rates (plan section 4: both still unmeasured).

    A temporary mailbox self-test (SRX_STAGE2_SELFTEST) injects 0x8001 into
    both CXD8501R mailboxes after boot and logs the acknowledge.  It exists
    only to exercise the page-1 main loop until the V810 host window is
    wired up in stage 3; remove it then.

    TODO (plan milestones):
      1. SERVO monitor UART (banner string at ROM offset 0x21CDA) -> TCP terminal
      2. Control-board CXD8501R + AD7874 models, DSP boot pages + BFORCE, IRQ1/2
      3. SERVO <-> Control windows 0x400000/0x400080
      4. CPU 8251/8254/8259, RTC, EEPROM image, PC card, slot kind bytes
      5. CPU <-> SERVO MB8421 DPRAM + IRQs, I/O boards, plant, safety panel

***************************************************************************/

#include "emu.h"

#include "cpu/i386/i386.h"
#include "cpu/v810/v810.h"
#include "cpu/adsp2100/adsp2100.h"

#include <algorithm>
#include <iterator>


namespace {

// Temporary bring-up test: 0x8001 into the mailbox to prove the page-1 main
// loop runs and acknowledges.  Remove when the V810 window exists (stage 3).
#define SRX_STAGE2_SELFTEST 1

// Guessed interrupt rates.  The real sources are still to be measured
// (plan section 4); only the ratios matter for keeping timeouts quiet.
static constexpr int DSP_IRQ1_HZ = 8000;    // ADC end-of-conversion / current loop
static constexpr int DSP_IRQ2_HZ = 8000;    // supervision tick (heartbeat every 0x2000 ticks)


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
		, m_dsp1_pm(*this, "dsp1_pm")
		, m_dsp2_pm(*this, "dsp2_pm")
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
	required_shared_ptr<uint32_t> m_dsp1_pm;
	required_shared_ptr<uint32_t> m_dsp2_pm;

	void maincpu_map(address_map &map);
	void maincpu_io_map(address_map &map);
	void servocpu_map(address_map &map);
	void dsp1_program_map(address_map &map);
	void dsp1_data_map(address_map &map);
	void dsp2_program_map(address_map &map);
	void dsp2_data_map(address_map &map);

	uint8_t diag_io_r();
	void diag_io_w(uint8_t data);

	// Stage 1: SERVO on-board peripheral block (0x300000..).  Writes are
	// logged; printable bytes are surfaced as console output.
	uint32_t servo_console_r(offs_t offset);
	void servo_console_w(offs_t offset, uint32_t data, uint32_t mem_mask);

	// Stage 2: Control board (2x ADSP-2115)
	cxd8501r_model m_cxd[2];
	uint16_t m_adc[2][4];
	unsigned m_adc_index[2];
	uint16_t m_outlatch[2];
	uint16_t m_syscntl[2];
	bool m_page1_active[2];
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
	map(0xffe00000, 0xffefffff).rom().region("maincpu", 0);    // 1 MB main flash (ROM1-C.bin)
	map(0xffff8000, 0xffffffff).rom().region("boot", 0);       // 32 KB boot EPROM (reset vector)
}

void srx_c61_state::maincpu_io_map(address_map &map)
{
	map(0x0020, 0x0020).rw(FUNC(srx_c61_state::diag_io_r), FUNC(srx_c61_state::diag_io_w)); // diagnostic/halt-code port
	// stage 4: 8251 x3 (C0/C4, C8/CC, D0/D4), 8254 (B0-BC), 8259 x2 (A0/A4, A8/AC),
	//           RTC (60-9C), EEPROM busy flag (0C), PC card (4C), slot latches (30-40)
}

// SERVO board (V810): ROM copied to RAM at 0 on boot.  gp = 0x2BAEC.
void srx_c61_state::servocpu_map(address_map &map)
{
	map(0x00000000, 0x0007ffff).ram();                         // 512 KB RAM at 0
	map(0x00100000, 0x0013ffff).rom().region("servocpu", 0);   // 256 KB flash (ROM_SERVO.bin)
	map(0xfffc0000, 0xffffffff).rom().region("servocpu", 0);   // reset alias (vector at 0xFFFFFFF0)

	// Stage 1: slot dual-port RAM (firmware initialises it and polls 0x200004
	// for the host handshake).  Modelled as plain RAM; the MB8421 mailboxes and
	// the CPU-side window arrive in stage 5.
	map(0x00200000, 0x00200fff).ram();

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

	// Trace stubs (plan 5.3): the DSP windows 0x400000/0x400080 arrive in stage 3.
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

// Stage 1: the SERVO 0x30000x block is the baud/SCI setup (observed command
// values 0x30/0x74/0xB4 and a 16-bit divisor).  The monitor does not emit its
// banner standalone: it idles polling slot DPRAM 0x200004 for the host
// handshake, so the console becomes useful once the CPU side exists (stage 5).
uint32_t srx_c61_state::servo_console_r(offs_t offset)
{
	return 0;
}

void srx_c61_state::servo_console_w(offs_t offset, uint32_t data, uint32_t mem_mask)
{
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
    Control board (stage 2)
***************************************************************************/

void srx_c61_state::dsp_set_line(int which, int line, int state)
{
	adsp2115_device &dsp = which ? *m_dsp2 : *m_dsp1;
	dsp.set_input_line(line, state);
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
	return m_cxd[which].regs[offset & 0x3f];
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
	uint16_t const result = m_adc[which][index];
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

void srx_c61_state::dsp_selftest(int unused)
{
	// Stage-2 acceptance aid only: no host is attached to the mailboxes yet.
	logerror("DSP self-test: injecting mailbox command 0x8001\n");
	dsp_cxd_w(0, 0x0000, 0x8001);
	dsp_cxd_w(1, 0x0000, 0x8001);
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

	// Guessed periodic sources (see the note at the top of the file).
	m_irq1_timer[0]->adjust(attotime::from_hz(DSP_IRQ1_HZ), 0, attotime::from_hz(DSP_IRQ1_HZ));
	m_irq1_timer[1]->adjust(attotime::from_hz(DSP_IRQ1_HZ), 1, attotime::from_hz(DSP_IRQ1_HZ));
	m_irq2_timer[0]->adjust(attotime::from_hz(DSP_IRQ2_HZ), 0, attotime::from_hz(DSP_IRQ2_HZ));
	m_irq2_timer[1]->adjust(attotime::from_hz(DSP_IRQ2_HZ), 1, attotime::from_hz(DSP_IRQ2_HZ));

#if SRX_STAGE2_SELFTEST
	m_selftest_timer->adjust(attotime::from_msec(500));
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
ROM_END

} // anonymous namespace


//    YEAR  NAME     PARENT  MACHINE  INPUT  CLASS          INIT       MONITOR  COMPANY  FULLNAME                          FLAGS
GAME(1995, srx_c61, 0,      srx_c61, 0,     srx_c61_state, empty_init, ROT0,   "Sony",  "SRX-611 SCARA Robot Controller",  MACHINE_NOT_WORKING | MACHINE_NO_SOUND)
