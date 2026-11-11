-- SRX-611 servo-cycle regression test (CI).
--
-- Needs a real .CTR block in the EEPROM NVRAM, e.g. the unit-1 U50 dump
-- patched for arm 82912 (see doc/robot_parameters.md section 4.4):
--
--   python3 tools/cpu/ctr_patch.py FW/SRX6-CPU/1/U50_AT28C64@SOIC28.bin \
--       <nvram>/srx_c61/eeprom_nv --l1 349.847 --l2 249.699 \
--       --home 200868 173395 18950 0
--   srx_c61 -video none -sound none -nothrottle -nvram_directory <nvram> \
--       -autoboot_script emu/tests/servo_cycle.lua
--
-- Checks (doc/servo_dsp_link.md section 7):
--   * the V810 CPU-link state machine (gp-0x3A2C) reaches state 2;
--   * the level-14 servo cycle runs: tick counter gp-0x3A28 advances about
--     SERVO_CYCLE_HZ per second (it stalls without the level-15 ADC EOC);
--   * the pendant shows neither E050 (parameter error) nor E030 (SVT
--     timeout 0x407E);
--   * the serial ABS reads (ABSCOPY $8082/$8084 on both DSPs) loaded the
--     CXD8501R counters with the power-on absolute values of the encoder
--     model (200868, 173395, 18950, 0).
--   E332-E335 ("encoder break", V810: encoder UVW-phase signal error) are
--   still expected: that input is not identified yet.
-- Prints "servo_cycle: PASS" or "servo_cycle: FAIL ..." and exits.

local machine = manager.machine
local io = machine.devices[":maincpu"].spaces["io"]
local sv = machine.devices[":servocpu"].spaces["program"]
local GP = 0x2BAEC
local ABS = { 200868, 173395, 18950, 0 }

-- CXD8501R counter of axis k (1..4) as the V810 reads it (sub_0A08).
local function counter(k)
	local base = 0x400000 + ((k - 1) >> 1) * 0x80 + (((k - 1) & 1) == 1 and 0x54 or 0x4c)
	return sv:read_u8(base + 2) * 65536 + sv:read_u16(base)
end

local function line(n)
	local s = ""
	io:write_u8(0xfa, n * 20)
	for i = 1, 20 do
		local c = io:read_u8(0xfb)
		s = s .. ((c >= 0x20 and c < 0x7f) and string.char(c) or ".")
	end
	return s
end

local tick0
emu.register_frame_done(function()
	local t = machine.time:as_double()
	if not tick0 and t >= 10.0 then
		tick0 = sv:read_u16(GP - 0x3a28)
	elseif tick0 and t >= 12.0 then
		local state = sv:read_u16(GP - 0x3a2c)
		local rate = ((sv:read_u16(GP - 0x3a28) - tick0) & 0xffff) / 2.0
		local l2 = line(1)
		print(string.format("servo_cycle: v810 state=%d cycle=%.0f Hz counters %d %d %d %d pendant [%s]",
			state, rate, counter(1), counter(2), counter(3), counter(4), l2))
		if state ~= 2 then
			print("servo_cycle: FAIL V810 link not in state 2")
		elseif rate < 500 or rate > 2000 then
			print("servo_cycle: FAIL level-14 servo cycle not running")
		elseif l2:find("ERR50") or l2:find("ERR30") then
			print("servo_cycle: FAIL controller stopped with E050/E030")
		elseif counter(1) ~= ABS[1] or counter(2) ~= ABS[2] or counter(3) ~= ABS[3] or counter(4) ~= ABS[4] then
			print(string.format("servo_cycle: FAIL encoder counters %d %d %d %d", counter(1), counter(2), counter(3), counter(4)))
		else
			print("servo_cycle: PASS")
		end
		machine:exit()
	end
end)
