-- SRX-611 EEPROM persistence test: the 8 KB parameter EEPROM at 0x600000 is
-- a MAME NVRAM device ("eeprom_nv") that is saved on exit and reloaded.
--
-- Run it twice with a scratch NVRAM directory, so the real one is untouched:
--   ./mame -rompath roms srx_c61 -video none -sound none -nothrottle \
--       -nvram_directory /tmp/srx_nv -seconds_to_run 3 \
--       -autoboot_script emu/tests/eeprom_nvram.lua
-- First run: "pattern written".  Second run: "PASS: pattern persisted".
-- The pattern goes into the last 16 bytes (0x601FF0..), outside the 6153-byte
-- .CTR block that the firmware reads (EEPROM offset 0..0x1808).

local cpu = manager.machine.devices[":maincpu"]
local prog = cpu.spaces["program"]
local io = cpu.spaces["io"]

local BASE = 0x601ff0
local frames = 0

local function pattern(i) return (0xa5 + i * 7) & 0xff end

emu.register_frame_done(function()
	frames = frames + 1
	if frames ~= 60 then return end

	local blank = true
	for a = 0x600000, 0x601808 do
		if prog:read_u8(a) ~= 0xff then blank = false break end
	end
	print(string.format("eeprom: .CTR area 0x600000-0x601808 is %s", blank and "blank (0xFF)" or "NOT blank"))
	print(string.format("eeprom: port 0x0C = %02x (bit 6 = write complete)", io:read_u8(0x0c)))

	local ok = true
	for i = 0, 15 do
		if prog:read_u8(BASE + i) ~= pattern(i) then ok = false break end
	end
	if ok then
		print("eeprom: PASS: pattern persisted from the previous run")
	else
		for i = 0, 15 do prog:write_u8(BASE + i, pattern(i)) end
		print("eeprom: pattern written to 0x601FF0; run again to check persistence")
	end
end)
