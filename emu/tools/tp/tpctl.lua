-- Interactive pendant control: commands in /work/cmd (one per line), results appended to /work/out.
--   key <col> <rowmask> <ms>   press, hold ms, release
--   wait <ms>
--   dump [tag]
--   peek <addr> <n>            CPU program bytes
local machine = manager.machine
local cpu = machine.devices[":maincpu"]
local io = cpu.spaces["io"]
local prog = cpu.spaces["program"]
local queue = {}
local tp = machine.devices[":tp"]
local tpprog = tp.spaces["program"]
cmdcount = {}
serlog = {}
local function slog(s) serlog[#serlog + 1] = string.format("%.3f %s", machine.time:as_double(), s); if #serlog > 80 then table.remove(serlog, 1) end end
ser_w = io:install_write_tap(0xc0, 0xc7, "serw", function(offset, data, mask)
	if offset ~= 0xc0 then ctl[#ctl + 1] = string.format("%.3f W%x=%08x/%08x", machine.time:as_double(), offset, data, mask) end
	slog(string.format("W%x=%02x", offset, data & 0xff)); return data end)
ctl = {}
ctl_w = io:install_write_tap(0xb0, 0xbf, "ctlw", function(offset, data, mask)
	ctl[#ctl + 1] = string.format("%.3f W%x=%08x/%08x", machine.time:as_double(), offset, data, mask); return data end)
rxf = {}
keycodes = {}
ser_r = io:install_read_tap(0xc0, 0xc7, "serr", function(offset, data, mask)
	if offset == 0xc0 then
		local b = data & 0xff
		slog(string.format("R%x=%02x", offset, b))
		if #rxf == 0 and b ~= 0x1b then return data end
		rxf[#rxf + 1] = b
		if #rxf >= 2 and #rxf == rxf[2] then
			if (rxf[3] == 0x10 or rxf[3] == 0x11) and rxf[2] > 6 then
				for i = 7, rxf[2] do keycodes[#keycodes + 1] = rxf[i] end
			end
			rxf = {}
		end
	end
	return data end)
cmdtap = tpprog:install_write_tap(0x827b, 0x827b, "tpcmd", function(offset, data, mask)
	cmdcount[data] = (cmdcount[data] or 0) + 1
	return data
end)
local busy_until = 0
local release_at = nil
local last_screen = ""

local function now() return machine.time:as_double() end
local function out(s)
	local f = io.open and nil
	local fh = _G.io.open("/work/out", "a"); fh:write(s .. "\n"); fh:close()
end
local function screen()
	local lines = {}
	for n = 0, 3 do
		local s = ""
		io:write_u8(0xfa, n * 20)
		for i = 1, 20 do
			local c = io:read_u8(0xfb)
			if c >= 0x20 and c < 0x7f then s = s .. string.char(c) else s = s .. string.format("{%02x}", c) end
		end
		lines[#lines + 1] = "|" .. s .. "|"
	end
	return table.concat(lines, "\n")
end

local pcs_left, pcs = 0, {}
-- "type" editor driver: closed loop on the CPU-side editor buffer
local ty = nil
local function type_step(t)
	local n = #ty.text
	local cur = prog:read_u8(ty.cur)
	local pos = nil
	for i = 0, n - 1 do
		local want = ty.text:sub(i + 1, i + 1)
		if want ~= "?" and string.char(prog:read_u8(ty.field + i)) ~= want then pos = i break end
	end
	if pos == nil or ty.steps > 3000 then
		local s = {}
		for i = 0, n - 1 do s[#s + 1] = string.char(prog:read_u8(ty.field + i)) end
		out(string.format("type done steps=%d field=[%s]", ty.steps, table.concat(s)))
		ty = nil
		return
	end
	ty.steps = ty.steps + 1
	local col, row
	if cur < pos then col, row = 2, 32        -- right
	elseif cur > pos then col, row = 0, 32    -- left
	else col, row = 2, 64 end                 -- scroll character
	io:write_u8(0xf8, col); io:write_u8(0xf9, row)
	release_at = t + 0.08; busy_until = t + 0.2
end
emu.register_frame_done(function()
	local t = now()
	if pcs_left > 0 then
		local pc = cpu.state["PC"].value - 0xffe00000
		pcs[pc] = (pcs[pc] or 0) + 1
		pcs_left = pcs_left - 1
		if pcs_left == 0 then
			local s = {}
			for k, v in pairs(pcs) do s[#s + 1] = {k, v} end
			table.sort(s, function(a, b) return a[2] > b[2] end)
			local o = {}
			for i = 1, math.min(12, #s) do o[#o + 1] = string.format("%x:%d", s[i][1], s[i][2]) end
			out("pcs " .. table.concat(o, " "))
		end
	end
	if release_at and t >= release_at then
		io:write_u8(0xf9, 0x00); release_at = nil
	end
	if t < busy_until then return end
	if ty then type_step(t) return end
	if #queue == 0 then
		local fh = _G.io.open("/work/cmd", "r")
		if fh then
			for l in fh:lines() do queue[#queue + 1] = l end
			fh:close(); os.remove("/work/cmd")
		end
		if #queue == 0 then return end
	end
	local l = table.remove(queue, 1)
	local w = {}
	for x in l:gmatch("%S+") do w[#w + 1] = x end
	if w[1] == "key" then
		io:write_u8(0xf8, tonumber(w[2])); io:write_u8(0xf9, tonumber(w[3]))
		local ms = tonumber(w[4] or "200")
		release_at = t + ms / 1000; busy_until = t + ms / 1000 + 0.4
	elseif w[1] == "raw" then
		io:write_u8(0xf8, tonumber(w[2])); io:write_u8(0xf9, tonumber(w[3]))
	elseif w[1] == "rtap" then
		local lo, hi = tonumber(w[2]), tonumber(w[3])
		rtaphits = {}
		rtap = prog:install_read_tap(lo, hi, "rtap", function(offset, data, mask)
			local k = string.format("%x<-%x", cpu.state["PC"].value - 0xffe00000, offset)
			rtaphits[k] = (rtaphits[k] or 0) + 1
			return data end)
	elseif w[1] == "rtapdump" then
		local o = {}
		for k, v in pairs(rtaphits or {}) do o[#o + 1] = k .. ":" .. v end
		table.sort(o); out("rtap " .. table.concat(o, " ")); rtap = nil; rtaphits = {}
	elseif w[1] == "find16" then
		local v = tonumber(w[2]); local o = {}
		for a = 0, 0x7fffe, 2 do if prog:read_u16(a) == v then o[#o + 1] = string.format("%x", a) end end
		out("find16 " .. table.concat(o, " "))
	elseif w[1] == "dw" then
		local a, n = tonumber(w[2]), tonumber(w[3]); local s = {}
		for i = 0, n - 1 do s[#s + 1] = string.format("%x:%08x", a + 4 * i, prog:read_u32(a + 4 * i)) end
		out("dw " .. table.concat(s, " "))
	elseif w[1] == "type" then
		ty = { field = tonumber(w[2]), cur = tonumber(w[3]), text = w[4], steps = 0 }
	elseif w[1] == "wait" then
		busy_until = t + tonumber(w[2]) / 1000
	elseif w[1] == "dump" then
		out(string.format("== %s t=%.2f\n%s", w[2] or "", t, screen()))
	elseif w[1] == "peek" then
		local a, n = tonumber(w[2]), tonumber(w[3]); local s = {}
		for i = 0, n - 1 do s[#s + 1] = string.format("%02x", prog:read_u8(a + i)) end
		out(string.format("peek %x: %s", a, table.concat(s, " ")))
	elseif w[1] == "cmds" then
		local s = {}
		for k, v in pairs(cmdcount) do s[#s + 1] = string.format("%02x:%d", k, v) end
		table.sort(s); out("cmds " .. table.concat(s, " ")); cmdcount = {}
serlog = {}
local function slog(s) serlog[#serlog + 1] = string.format("%.3f %s", machine.time:as_double(), s); if #serlog > 80 then table.remove(serlog, 1) end end
ser_w = io:install_write_tap(0xc0, 0xc7, "serw", function(offset, data, mask)
	if offset ~= 0xc0 then ctl[#ctl + 1] = string.format("%.3f W%x=%08x/%08x", machine.time:as_double(), offset, data, mask) end
	slog(string.format("W%x=%02x", offset, data & 0xff)); return data end)
ctl = {}
ctl_w = io:install_write_tap(0xb0, 0xbf, "ctlw", function(offset, data, mask)
	ctl[#ctl + 1] = string.format("%.3f W%x=%08x/%08x", machine.time:as_double(), offset, data, mask); return data end)
rxf = {}
keycodes = {}
ser_r = io:install_read_tap(0xc0, 0xc7, "serr", function(offset, data, mask)
	if offset == 0xc0 then
		local b = data & 0xff
		slog(string.format("R%x=%02x", offset, b))
		if #rxf == 0 and b ~= 0x1b then return data end
		rxf[#rxf + 1] = b
		if #rxf >= 2 and #rxf == rxf[2] then
			if (rxf[3] == 0x10 or rxf[3] == 0x11) and rxf[2] > 6 then
				for i = 7, rxf[2] do keycodes[#keycodes + 1] = rxf[i] end
			end
			rxf = {}
		end
	end
	return data end)
	elseif w[1] == "pcs" then
		pcs_left = tonumber(w[2]); pcs = {}; busy_until = t + pcs_left / 50 + 0.5
	elseif w[1] == "find32" then
		local lo, hi = tonumber(w[2]), tonumber(w[3]); local o = {}
		for a = 0, 0x7fffc, 4 do
			local v = prog:read_u32(a)
			if v >= lo and v <= hi then o[#o + 1] = string.format("%x=%x", a, v) end
		end
		out("find32 " .. table.concat(o, " "))
	elseif w[1] == "codeptrs" then
		local a0, n = tonumber(w[2]), tonumber(w[3]); local o = {}
		for a = a0, a0 + n * 4 - 4, 4 do
			local v = prog:read_u32(a)
			if v >= 0xffe00000 and v < 0xffee0000 then o[#o + 1] = string.format("%x:%x", a, v - 0xffe00000) end
		end
		out("codeptrs " .. table.concat(o, " "))
	elseif w[1] == "tppeek" then
		local a, n = tonumber(w[2]), tonumber(w[3]); local s = {}
		for i = 0, n - 1 do s[#s + 1] = string.format("%02x", tpprog:read_u8(a + i)) end
		out(string.format("tppeek %x: %s  tpPC=%x", a, table.concat(s, " "), tp.state["PC"].value))
	elseif w[1] == "ctl" then
		out("ctl\n" .. table.concat(ctl, "\n"))
	elseif w[1] == "keys" then
		local o = {}
		for _, k in ipairs(keycodes) do o[#o + 1] = string.format("%02x", k) end
		out(string.format("keys %s %s", w[2] or "", table.concat(o, " "))); keycodes = {}
	elseif w[1] == "serlog" then
		out("serlog\n" .. table.concat(serlog, "\n"))
	elseif w[1] == "quit" then
		machine:exit()
	end
end)
