-- SRX-611 stage 5 test: DPRAM peer playback + safety / field-I/O injection
--
-- Run with:
--   ./mame -rompath roms srx_c61 -video none -sound none -nothrottle \
--       -seconds_to_run 15 -log -oslog \
--       -autoboot_script emu/tests/stage5_safety.lua
--
-- Why the CPU peer is played from Lua: the CPU firmware's config load and
-- validation fail on the blank EEPROM (plan 6.1, P1).  INIT therefore never
-- calls the slot bring-up at 0x74A4 and never writes the slot-1 handshake
-- itself.  This script drives the CPU side of the shared DPRAM the way
-- de_cntrl (0x5A70 family) would, so the V810 mailbox/IRQ path is exercised
-- while the real EEPROM image is still missing.
--
-- Driver control registers (CPU I/O space):
--   0xF0  safety faults (bit0 E-stop, bit1 DSS off, bit2 AMPRDY, bit3 over-speed)
--   0xF1  field input word low byte
--   0xF2  field input word high byte
--   0xF3  last I/O-board output word low byte   (read)
--   0xF4  last I/O-board output word high byte  (read)
--   0xF5  SERVO DPRAM mailbox byte              (read)
--   0xF6  slot-1 IRQ pending bits               (read)
--
-- Shared slot-1 DPRAM (CPU program space, CPU-side little-endian):
--   0x700004  handshake word   (CPU writes 0xFFFF)
--   0x700010  doorbell         (CPU sets 1 after the axis writes)
--   0x700FFC  mailbox          (V810 writes, CPU read acknowledges)

local machine = manager.machine
local cpu = machine.devices[":maincpu"]
local io = cpu.spaces["io"]
local prog = cpu.spaces["program"]

local frames = 0
local DSS_OFF = 0x02

local function show(tag)
	local mailbox = io:read_u8(0xf5)
	local irq = io:read_u8(0xf6)
	print(string.format("stage5: %s mailbox=%02x irq=%02x", tag, mailbox, irq))
end

emu.register_frame_done(function()
	frames = frames + 1

	if frames == 120 then
		-- Play the CPU side of the slot-1 handshake.
		prog:write_u16(0x700004, 0xffff)
		print(string.format("stage5: CPU peer wrote handshake 0xFFFF at 0x700004 (readback %04x)", prog:read_u16(0x700004)))
		show("after handshake")
	elseif frames == 140 then
		prog:write_u16(0x700010, 0x0001)
		print(string.format("stage5: CPU peer set doorbell 1 at 0x700010 (readback %04x)", prog:read_u16(0x700010)))
	elseif frames == 200 then
		show("after doorbell")
		print(string.format("stage5: mail dump ffc=%02x ffd=%02x iof5=%02x", prog:read_u8(0x700ffc), prog:read_u8(0x700ffd), io:read_u8(0xf5)))
		local mailbox = prog:read_u16(0x700ffc)
		print(string.format("stage5: CPU peer read mailbox word %04x (ack)", mailbox))
		show("after ack")
		-- Flip the DSS input (E401 path) and restore it.
		io:write_u8(0xf0, DSS_OFF)
		print("stage5: DSS off (E401 path armed)")
	elseif frames == 320 then
		io:write_u8(0xf0, 0x00)
		print("stage5: DSS on (all clear)")
	elseif frames == 400 then
		show("final")
	end
end)
