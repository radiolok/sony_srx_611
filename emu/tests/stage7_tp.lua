-- SRX-611 stage 7 test: real teach-pendant firmware (Z180) over CPU ch1.
--
-- Run with:
--   ./mame -rompath roms srx_c61 -video none -sound none -nothrottle \
--       -seconds_to_run 8 -log -oslog \
--       -autoboot_script emu/tests/stage7_tp.lua
--
-- The two real firmwares do the "SRX6"/"TP4" handshake themselves; the driver
-- logs it.  This script reads the pendant's 20x4 LCD text through the CPU I/O
-- readback ports and injects one key into the matrix:
--   0xF8  key column (0-6)
--   0xF9  key rows for that column (bit set = pressed)
--   0xFA  display read index (0-79, line-major)
--   0xFB  display character, auto-incrementing
-- The pendant's key-scan result is read straight from its RAM (0x800F..).

local machine = manager.machine
local cpu = machine.devices[":maincpu"]
local tp = machine.devices[":tp"]
local io = cpu.spaces["io"]
local tpprog = tp.spaces["program"]

local frames = 0

local function line(n)
	local s = ""
	io:write_u8(0xfa, n * 20)
	for i = 1, 20 do
		local c = io:read_u8(0xfb)
		if c >= 0x20 and c < 0x7f then
			s = s .. string.char(c)
		else
			s = s .. "."
		end
	end
	return s
end

local function dump(tag)
	print(string.format("stage7: %s", tag))
	for n = 0, 3 do
		print(string.format("stage7: LCD L%d [%s]", n + 1, line(n)))
	end
end

emu.register_frame_done(function()
	frames = frames + 1
	if frames == 150 then
		io:write_u8(0xf8, 0)       -- key matrix column 0
		io:write_u8(0xf9, 0x01)    -- row 0 pressed
		print("stage7: injected key column 0 row 0")
	elseif frames == 300 then
		dump("after handshake / CPU screens")
		print(string.format("stage7: TP key-scan RAM 0x800F = %02x (with key held)", tpprog:read_u8(0x800f)))
	elseif frames == 550 then
		print(string.format("stage7: TP key-scan RAM 0x800F = %02x (~9 s, key held)", tpprog:read_u8(0x800f)))
		io:write_u8(0xf9, 0x00)
		print("stage7: released key")
	elseif frames == 650 then
		print(string.format("stage7: TP key-scan RAM 0x800F = %02x (released)", tpprog:read_u8(0x800f)))
	end
end)
