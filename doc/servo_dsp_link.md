# SERVO board ↔ Control board link (V810 side of the DSP mailbox)

How the SRX6-SERVO board (NEC V810, `FW/SRX6-SERVO/ROM_SERVO.bin`) talks to the two
ADSP-2115 DSPs of the Control board. DSP side: `doc/control_board_firmware.md`. Boards:
`doc/hardware_overview.md`.

Tool: `tools/v810/v810dis.py` (linear V810 disassembler with constant tracking). Peripheral
address constants used by the firmware: `FW/SRX6-SERVO/ROM_SERVO_periph.txt`.

Confidence tags: **[C]** confirmed by code on both sides; **[I]** inferred, likely;
**[H]** hypothesis.

---

## 1. V810 memory layout (as far as needed here)

- Reset: `movhi 0x10,r0,r31; jmp [r31]` → ROM at `0x00100000`. The start-up code copies the
  whole 256 KB ROM to RAM at **address 0** and runs from there. So **run-time addresses =
  file offsets** (`--base 0`). [C]
- `gp = 0x0002BAEC` (set at `0x0110`); globals are `gp`-relative. Run the tool with
  `--seed gp=0x2BAEC`. [C]
- Stack top `0x0007F800`. The last 512 bytes of ROM (`0x3FE00–0x3FFFF`) are copied to
  `0x7FE00`. [C]

| V810 address | What | Evidence |
|---|---|---|
| `0x200000–0x200FFF` | **slot DPRAM to the CPU board** (2× MB8421). `+0xF00` version string, `+0xFFC` mailbox / IRQ word | same offsets as the CPU side `0x700000+(s−1)·0x10000` (architecture report §8.4) [C] |
| `0x300000–0x31FFFF` | on-board registers (LEDs, I/O, …); `0x308004 = 0xFF` at boot | [I] |
| `0x400000–0x40007F` | **DSP 1 window** = DSP DM `$3000–$303F` (CXD8501R #1) | byte offset / 2 = DSP word [C] |
| `0x400080–0x4000FF` | **DSP 2 window** = DSP DM `$3000–$303F` (CXD8501R #2) | same layout, +0x80 [C] |
| `0x500000…` | another peripheral (not studied) | [H] |

So the SERVO board reaches each DSP's CXD8501R register block as 64 16-bit words, word *n*
at byte `2n`. The hardware path is almost certainly the **50-pin cable** from the SERVO front
connector (TX3-50P) to the Control board. [I]

## 2. Pointer table in RAM (initialised data)

The firmware keeps the window addresses in a table at `0x23B44` (`gp−0x7FA8`). [C]

| gp offset | Value | DSP word | Use |
|---|---|---|---|
| `−0x7FA8` / `−0x7FA4` | `0x400000` / `0x400080` | `$3000` | **command word**, DSP 1 / DSP 2 |
| `−0x7FA0` / `−0x7F9C` | `0x400004` / `0x400084` | `$3002` | **status word** (bits 1/2 = motor A/B current loop on) |
| `−0x7F98` / `−0x7F94` | `0x400042` / `0x4000C2` | `$3021` | ASIC control/status |
| `−0x7F90` / `−0x7F8C` | `0x400044` / `0x4000C4` | `$3022` | ASIC fault/enable |
| `−0x7F88` / `−0x7F84` | `0x40007E` / `0x4000FE` | `$303F` | ASIC status (bits 2–3 `0x000C` set by the V810) |
| `−0x7F80`, `−0x7F7C` | `0x400012`, `0x400016` | `$3009`, `$300B` | DSP 1 **inputs written by SERVO** (per motor, from axis structures; meaning open) — not the ABS result |
| `−0x7F78`, `−0x7F74` | `0x400092`, `0x400096` | `$3009`, `$300B` | same, DSP 2 |
| `−0x7F70…−0x7F64` | `0x40004C/4E/54/56` | `$3026/27/2A/2B` | DSP 1 **24-bit position counters**: motor A = `$3027` (byte, bits 23..16) : `$3026`; motor B = `$302B` : `$302A` (`doc/abs_encoder_protocol.md`) |
| `−0x7F60…−0x7F54` | `0x4000CC/CE/D4/D6` | `$3026/27/2A/2B` | DSP 2 position counters (axes 3, 4) |
| `−0x7F50` | `0x40004A` | `$3025` | DSP 1 ASIC control |

Other direct accesses: `$3001` (data word, ×10 sites), `$3003`, `$3004–$3007` (monitor
words), `$300C–$300F`, `$3023`, `$3029`/`$302D` (per-motor, accessor at `0x0BB4`),
`$302F`, `$3030`/`$3031` (driver module ID / status, read at `0x1D28`, `0x22D4`). [C]

## 3. Handshake

`sub_0888` (DSP 1) and `sub_08E8` (DSP 2) **wait for acknowledge**. They poll the command
word until it reads `0`, up to 10 000 × a 50-step delay loop, and return 1 = acked or
0 = timeout. This matches the DSP main loop, which writes `0` to `$3000` when a command is
done. [C]

Sending a command: write the argument to `$3001` (if any), write the command word to
`$3000`, then call the wait routine. [C]

## 4. Commands the V810 sends

| Command | Where (V810) | DSP action | Meaning |
|---|---|---|---|
| `0x8001` | `sub_0948` (from init `0x026C` and `0xDE98`) — to **both** DSPs | enable request: checks FLAG_IN and driver ready bits, acks | **CONNECT / initialise amplifier** [C][I] |
| `0x8002` / `0x8004` | `0x1110` (motor A on), `0x1178` (motor B on) | mode 2 / 4 → current loop on for motor A / B | **servo ON one motor** [C] |
| `0x8006` | `sub_12B0` | mode 6 → both motors | **servo ON both** (used when the other motor is already on) [C] |
| `0x8000` | `0x13F0`… (×14 sites) | mode 0 → both off | **servo OFF**; if the other motor stays on, `0x8002`/`0x8004` is sent instead [C] |
| `0x8082` / `0x8084` | `sub_3080(axis 0..3)` — DSP 1 A, DSP 1 B, DSP 2 A, DSP 2 B; output bit `0x2000` cleared before, set after | handled in the DSP **IRQ2** path (`loc_01E2`, mask `0xFFEF`): starts the **SPORT0** state machine | **read the serial absolute encoder of motor A/B** — the monitor's `ABSCOPY (axis) -> UPDATE COUNTER FROM SERIAL ABS` [I] |
| `0xD8A8` / `0xD8A9` + data `0x3865` / `0x3874` | `0x0D8C` (from `0x03A8`) | **poke** DSP DM `$38A8` / `$38A9` | select the variables shown on the two **analog monitor outputs** (`$1000/$1001`) and in mailbox words `$3004/$3005` [C] |
| `0xD8AA` / `0xD8AB` + data `0x38C5…0x38C8` | `sub_0E3C(axis)` | poke `$38AA` / `$38AB` | select the variables returned in mailbox monitor words `$3006/$3007` [C][I] |

Not found in the V810 code: `0x9002`, generic `0xCxxx` peeks, and the page-2 magic
`0x4123,0x1002`. The page-2 ADC/calibration mode and free peek/poke are probably reached
only from the monitor console (`RMTCMD`, typed by a service engineer) or from a factory
tool. [H]

**Peek/poke address field (DSP side, now confirmed by the V810's use):** the low 12 bits
select the address. `0x000–0x7FF` → **PM** `0x000–0x7FF`; `0x800–0xFFF` → **DM**
`0x3800–0x3FFF` (internal RAM). Example: `0xD8A8` → DM `$38A8`. [C]

## 5. Axis numbering

The monitor strings `AMP ERROR(axis 1/2): …` and `AMP ERROR(axis 3/4): …` and the per-axis
switch tables (`sub_3080`, `sub_0BB4`, `sub_0E3C`) agree: [C]

| Robot axis | DSP | Motor in pair | Window |
|---|---|---|---|
| 1 | DSP 1 | A | `0x400000` |
| 2 | DSP 1 | B | `0x400000` |
| 3 | DSP 2 | A | `0x400080` |
| 4 | DSP 2 | B | `0x400080` |

## 6. What this says about the encoders

Worked out in detail in `doc/abs_encoder_protocol.md`. In short: [C][I]

- The encoder lines **end at the Control board**. The serial absolute encoder is read by the
  DSP on SPORT0 (receive-only, 16× oversampled; a motor A/B multiplexer selected by `$3200`
  bit 0). Frame = two 24-bit blocks with CRC-5 (x⁵+x²+1).
- The decoded 24-bit position is loaded into the CXD8501R **24-bit position counters**
  (`$3026/$3027`, `$302A/$302B`), which then count incrementally. The SERVO board reads them
  as signed 24-bit positions (`sub_0A08`) and can preset them.
- Status byte per motor → `$3003`, read by the SERVO at `0x1D60`.

## 7. Next steps

1. Name the V810 functions around the mailbox (`0x0948`, `0x1110…0x1600`, `0x3080`, `0x0BB4`)
   via the monitor command table near string `0x23DE8` (`CONNECT`, `MODE`, `RMTCMD`,
   `MODEL`, `ABSCOPY`).
2. ~~Decode the SPORT0 serial-ABS state machine~~ — done: `doc/abs_encoder_protocol.md`
   (result → counters `$3026/27`, `$302A/2B`, status → `$3003`).
3. Map the SERVO side of the CPU DPRAM (`0x200000…`) to the per-axis fields that the CPU
   firmware uses (architecture report §8.4).
