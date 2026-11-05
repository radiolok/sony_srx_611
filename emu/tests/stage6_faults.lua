-- SRX-611 stage 6 test: external fault switches and their firmware consumers
--
-- Run with:
--   ./mame -rompath roms srx_c61 -video none -sound none -nothrottle \
--       -seconds_to_run 20 -log -oslog \
--       -autoboot_script emu/tests/stage6_faults.lua
--
-- Fault switches (CPU I/O space, driver control register):
--   0xF0  fault bits: 0x01 E-stop, 0x02 DSS off, 0x04 AMPRDY fail,
--                     0x08 SPD over-speed, 0x10 driver fault
--   0xF7  ADC offset, signed 8-bit (added to every AD7874 channel)
--
-- Firmware consumers (file offsets = runtime address - 0xFFE00000):
--   E401 DSS off    : app_3BD28 0x3BD28 -> sys_req_27h(...,0x191) at 0x3BE1B
--                     input = RAM 0x62B8 bit 6, read by app_10C5C(7)
--   E400 over-speed : SVT AMP-status parser 0x3B8B8, bit 0x4000 ->
--                     sys_req_27h(...,0x190) at 0x3BAF1
--   E300 E-stop     : same parser, bit 0x1000 -> code 0x12C
--   E340 driver     : same parser, bit 0x0400 -> code 0x154
--   E341 AMPRDY     : same parser, bit 0x80000 -> code 0x155
--
-- The test does two things:
--   1. proves each switch is wired to the real firmware input the consumer
--      uses (RAM 0x62B8 bit 6 for DSS; the slot-1 per-axis status dword for
--      the servo faults; the AD7874 channel offset for the ADC case);
--   2. reports whether the firmware actually raised the error, and prints
--      the blocker when it did not.  The blank EEPROM (plan 6.1) makes
--      0x300F0/0x8BD4 fail, INIT skips servo bring-up 0x74A4, the SVT servo
--      cycle 0x37840 never runs and 0x74CB[axis] stays 0, so app_3BD28
--      returns 0x4080 before its DSS test.  E401/E400 are therefore NOT
--      reproduced as error requests; the test prints the evidence instead of
--      faking a code.

local machine = manager.machine
local cpu = machine.devices[":maincpu"]
local io = cpu.spaces["io"]
local prog = cpu.spaces["program"]
local dsp1_data = machine.devices[":dsp1"].spaces["data"]

local frames = 0
local ES, DSS, AMPRDY, OVERSPEED, DRIVER = 0x01, 0x02, 0x04, 0x08, 0x10

-- Track whether the firmware ever configured an axis (SVT writes
-- 0x74CB[channel]=1 at 0x37B46 when the servo link comes up).
local axis_configured_seen = false
local mailbox_irq_seen = false

local function rd16(a) return prog:read_u16(a) end
local function rd8(a) return prog:read_u8(a) end

local function show(tag)
	print(string.format(
		"stage6: %-22s 62b8=%04x (DSS bit6=%d) 6230=%04x 74cb=%02x 74a8=%08x",
		tag, rd16(0x62b8), (rd16(0x62b8) >> 6) & 1, rd16(0x6230),
		rd8(0x74cb), prog:read_u32(0x74a8)))
end

local function axis_status()
	-- per-axis block 0 status dword, CPU-side (fault bits are OR-ed here)
	return prog:read_u32(0x700100)
end

emu.register_frame_done(function()
	frames = frames + 1

	if rd8(0x74cb) ~= 0 then axis_configured_seen = true end
	if (io:read_u8(0xf6) & 0x03) ~= 0 then mailbox_irq_seen = true end

	if frames == 120 then
		print("stage6: --- baseline (all switches clear) ---")
		show("baseline")
		print(string.format("stage6: E401 source check: 0x191 immediate at 0xFFE3BE1F = 0x%x",
			prog:read_u32(0xffe3be1f)))
		print(string.format("stage6: E400 source check: 0x190 immediate at 0xFFE3BAF5 = 0x%x",
			prog:read_u32(0xffe3baf5)))
	elseif frames == 140 then
		io:write_u8(0xf0, DSS)
		print("stage6: DSS off -> E401 input armed")
	elseif frames == 200 then
		show("after DSS off")
		print(string.format("stage6: DSS result: firmware input 0x62B8 bit6=%d (0 = DSS off)",
			(rd16(0x62b8) >> 6) & 1))
	elseif frames == 220 then
		io:write_u8(0xf0, 0x00)
		print("stage6: DSS on (all clear)")
	elseif frames == 280 then
		show("after DSS on")
	elseif frames == 300 then
		io:write_u8(0xf0, OVERSPEED)
		print(string.format("stage6: over-speed on -> slot-1 axis status 0x%05x (want 0x04000)",
			axis_status() & 0xfffff))
	elseif frames == 320 then
		io:write_u8(0xf0, DRIVER)
		print(string.format("stage6: driver fault on -> slot-1 axis status 0x%05x (want 0x00400)",
			axis_status() & 0xfffff))
	elseif frames == 340 then
		io:write_u8(0xf0, AMPRDY)
		print(string.format("stage6: AMPRDY fail on -> slot-1 axis status 0x%05x (want 0x80000)",
			axis_status() & 0xfffff))
	elseif frames == 360 then
		io:write_u8(0xf0, ES)
		print(string.format("stage6: E-stop on -> slot-1 axis status 0x%05x (want 0x01000)",
			axis_status() & 0xfffff))
	elseif frames == 380 then
		io:write_u8(0xf0, 0x00)
		io:write_u8(0xf7, 0x10)
		print("stage6: all clear; ADC offset = +16")
	elseif frames == 400 then
		print(string.format("stage6: DSP1 AD7874 channel read with offset = %d (want 16)",
			dsp1_data:read_u16(0x3400)))
	elseif frames == 460 then
		io:write_u8(0xf7, 0x00)
		print("stage6: ADC offset back to 0")
	elseif frames == 520 then
		show("final")
		print(string.format("stage6: axis configured (SVT wrote 0x74CB) = %s",
			tostring(axis_configured_seen)))
		print(string.format("stage6: slot-1 mailbox IRQ ever asserted = %s",
			tostring(mailbox_irq_seen)))
		print(string.format("stage6: EEPROM first bytes at 0x600000 = %02x %02x %02x %02x (blank 0xFF = no config)",
			rd8(0x600000), rd8(0x600001), rd8(0x600002), rd8(0x600003)))
		if not axis_configured_seen then
			print("stage6: VERDICT E401/E400: NOT RAISED.  Cause: blank EEPROM ->")
			print("stage6:   0x300F0/0x8BD4 config validation fails -> INIT skips")
			print("stage6:   0x74A4 servo bring-up -> SVT 0x37840 never runs ->")
			print("stage6:   0x74CB stays 0 -> app_3BD28 0x3BD28 returns 0x4080")
			print("stage6:   before the DSS test; over-speed parser 0x3B8B8 is")
			print("stage6:   only called from SVT (0x37D72).  Switch wiring is shown")
			print("stage6:   above; no error code was fabricated.")
		else
			print("stage6: VERDICT: axis configured; the firmware error path is reachable,")
			print("stage6:   check the SRX SAFETY / sys_req_27h trace for the E-code.")
		end
	end
end)
