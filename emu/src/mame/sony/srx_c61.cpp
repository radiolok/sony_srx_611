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


namespace {

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
	// trace stubs (plan 5.3): 0x200000 DPRAM, 0x300000 on-board regs,
	//                         0x400000/0x400080 DSP windows, 0x500000 second peripheral
}

// Control board (ADSP-2115 #1): 1K x 24-bit internal program RAM.
void srx_c61_state::dsp1_program_map(address_map &map)
{
	map(0x0000, 0x03ff).ram().share(m_dsp1_pm);
}

void srx_c61_state::dsp1_data_map(address_map &map)
{
	map(0x0000, 0x03ff).ram();                                 // 1K x 16-bit internal data RAM
	// stage 2: CXD8501R @ 0x3000-0x303F, output latch @ 0x3200, AD7874 @ 0x3400
}

// Control board (ADSP-2115 #2).
void srx_c61_state::dsp2_program_map(address_map &map)
{
	map(0x0000, 0x03ff).ram().share(m_dsp2_pm);
}

void srx_c61_state::dsp2_data_map(address_map &map)
{
	map(0x0000, 0x03ff).ram();
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
    Machine start
***************************************************************************/

void srx_c61_state::machine_start()
{
	// Load the first ADSP boot page (page 0 = loader/init) into each DSP's
	// internal program RAM.  Page 1 (run time) is loaded by page 0 via BFORCE;
	// that is handled in stage 2.
	m_dsp1->load_boot_data(memregion("dsp1")->base(), m_dsp1_pm);
	m_dsp2->load_boot_data(memregion("dsp2")->base(), m_dsp2_pm);
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
