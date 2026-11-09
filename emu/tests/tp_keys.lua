-- SRX-611 pendant key regression test (CI).
--
-- With a blank EEPROM the controller boots into E050 ("controller parameter
-- error") on the pendant.  F4 closes the error and shows the teach screen.
-- The key is pressed at t = 15 s, i.e. after the point where an edge-only
-- Z180 ASCI RX interrupt used to desynchronise the CPU -> TP link (see
-- emu/patches/0001-z180asci-rdrf-level-irq.patch).  Prints "tp_keys: PASS"
-- or "tp_keys: FAIL ..." and exits.
--
--   srx_c61 -video none -sound none -nothrottle -seconds_to_run 30 \
--       -autoboot_script emu/tests/tp_keys.lua

local machine = manager.machine
local io = machine.devices[":maincpu"].spaces["io"]

local function line(n)
	local s = ""
	io:write_u8(0xfa, n * 20)
	for i = 1, 20 do
		local c = io:read_u8(0xfb)
		s = s .. ((c >= 0x20 and c < 0x7f) and string.char(c) or ".")
	end
	return s
end

local step = 0
emu.register_frame_done(function()
	local t = machine.time:as_double()
	if step == 0 and t >= 14.5 then
		local l2 = line(1)
		print(string.format("tp_keys: before F4 line2 [%s]", l2))
		if not l2:find("ERR50") then
			print("tp_keys: FAIL no E050 screen before the key press")
			machine:exit()
		end
		step = 1
	elseif step == 1 and t >= 15.0 then
		io:write_u8(0xf8, 4)       -- column 4
		io:write_u8(0xf9, 0x80)    -- row 7 = F4
		step = 2
	elseif step == 2 and t >= 15.3 then
		io:write_u8(0xf9, 0x00)
		step = 3
	elseif step == 3 and t >= 17.0 then
		local l1, l2 = line(0), line(1)
		print(string.format("tp_keys: after F4 line1 [%s] line2 [%s]", l1, l2))
		if l1:find("R1") and l1:find("here") and not l2:find("ERR50") then
			print("tp_keys: PASS (F4 closed E050, teach screen shown)")
		else
			print("tp_keys: FAIL (key not handled; pendant link desynchronised?)")
		end
		machine:exit()
	end
end)
