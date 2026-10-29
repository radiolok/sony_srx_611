# Control board (2× ADSP-2115) — firmware, first pass

First look at the DSP firmware of the SRX-C61 **Control board** (1-659-417-12): the board
in the drive section that sits between the SERVO board and the four motor drivers. Board
hardware: `doc/hardware_overview.md` §7.

- **Images:** `FW/SERVO_IO/1/U7_M27C512@DIP28.BIN` and `FW/SERVO_IO/1/U18_M27C512@DIP28.BIN`
  (folder name kept from before the board was identified). The two files are
  **byte-identical** (MD5 `b8a7a0abc2ddea7cb1dfd694385a06ed`): both DSPs run the same code.
- **Tool:** `tools/adsp/adsp21xx.py` (boot-page unpacker + disassembler + DM cross-reference).
- **Generated outputs:** `FW/SERVO_IO/1/U7_dis.asm` (full listing),
  `FW/SERVO_IO/1/U7_xref.md` (DM access tables).

Confidence tags: **[C]** confirmed by the code; **[I]** inferred, likely; **[H]** hypothesis.

---

## 1. Why this is ADSP-21xx boot data (not V810 code)

- Every 4th byte is `0xFF` (16381 of 16384), except byte 3 of each boot page. This is the
  ADSP-2101/2115 byte-wide boot format: 3 bytes per 24-bit instruction plus one pad byte.
  The pad byte of word 0 holds the page length. [C]
- The board carries **two ADSP-2115** and **two identical EPROMs "C6A06 V2.07"** — matching
  two identical dumps. [C]
- The first instructions decode as a typical ADSP-21xx start-up: DAG M/L register init,
  SPORT0 set-up, wait states, ICNTL, mode bits, RAM clear. [C]

## 2. Boot pages

| Page | EPROM offset | Words | Role |
|---|---|---|---|
| 0 | `$00000` | 192 (`$17`) | **Loader/initialiser.** Sets DAG registers, SPORT0, DM wait states; clears internal DM and `$3000–$301F`; reads board straps; copies parameter tables from PM into internal DM; then reboots into page 1 (`SYSCNTL = $0258` → BPAGE 1, BFORCE). [C] |
| 1 | `$02000` | 1024 (`$7F`, full internal PM) | **Run-time firmware:** host command mailbox, current loop, PWM, status, serial link. [C] |
| 2 | `$04000` | 72 (`$08`) | **ADC measurement mode** (calibration / offset test). Entered from page 1 on a magic command. [C][I] |

Page 1 relies on M0–M7 values left by page 0 (`M0=0, M1=1, M2=-1, M3=0, M4=0, M5=1,
M6=-1, M7=0`). A BFORCE soft reboot reloads PM only. The tool assumes these values for
later pages (`--no-seed` turns that off). [C]

## 3. System set-up (page 0 / page 1)

| Register | Value | Meaning |
|---|---|---|
| `SP0_RFSDIV` `$3FF4` | `$000F` | receive frame every 16 SCLK [C] |
| `SP0_SCLKDIV` `$3FF5` | `$001B` | SCLK = CLKOUT / 56 [C] |
| `SP0_CTRL` `$3FF6` | `$410F` | 16-bit words, internal RFS, internal SCLK → **the DSP is the clock master of SPORT0** [C] |
| `DM_WAIT` `$3FFE` | `$253F` | DWAIT0=7, DWAIT1=7, DWAIT2=4, DWAIT3=2, DWAIT4=2 [C] |
| `SYSCNTL` `$3FFF` | `$101A` (page 1, 2) | PWAIT=2, SPORT0 enabled, SPORT1 off → its pins act as **IRQ0/IRQ1/FLAG_IN/FLAG_OUT** [C] |
| `IMASK` | `$002C` | **IRQ2, SPORT0 RX and IRQ1** enabled; timer and SPORT0 TX off [C] |

Register addresses and bit meanings follow the ADSP-2101/2115 data sheet. The names in
the tool's `CTRL_REGS` table should be checked once more against the data sheet. [I]

## 4. Data-memory map as used by the code

| DM address | Device (inferred) | What the code does with it | |
|---|---|---|---|
| `$3000` | CXD8501R **host mailbox**: command word | main loop copies `$3000–$301F` into internal RAM `$3888…`, decodes the command at `$3000`, then writes `0` back to `$3000` (acknowledge) | [C][I] |
| `$3001` | mailbox: reply | result of a peek command | [C] |
| `$3002`, `$3003` | mailbox: status words | written with status bits from `$38B1` / fault bits | [C] |
| `$3004–$3007` | mailbox: 4 monitor words | values picked by four pointers at `$38A8…` (a "watch" feature) | [C] |
| `$3016–$301F` | mailbox: per-channel blocks (stride 5) | read by the control code; probably current references and parameters per motor | [C][I] |
| `$3021` | ASIC control/status | bit 7 (`$0080`), bits 7–9 (`$0380`), bits 13–15 (`$E000`) read; `$60/$61/$80/$81/$03` written | [C] |
| `$3022`, `$3023` | ASIC fault/enable bits | bits 0–2 written `6`/`7`; read back in the IRQ2 handler | [C][I] |
| `$3025` | ASIC control | `$0080` after each ADC cycle (page 2), `$000F` before reboot into page 2 | [C] |
| `$3029`, `$302D` | ASIC per-motor counters/latches (motor A / B) | DSP reads them twice and compares (stable read of a running value); page 0 sets them from tables; the SERVO board reads them per axis (`sub_0BB4`) — incremental position counters? | [C][H] |
| `$3030` | **driver module ID + ready bits** | bits 0–3 / 8–11: 4-bit module code per motor (`8`, `9`, `A`, `C` known); bits 4 / 12 (`$1010`, active low): ready/fault per motor | [C][I] |
| `$3033` | **PWM carrier period** | `1000` (`$03E8`) at start; `$0FFF` before entering page 2 | [C][I] |
| `$3034–$3036` | PWM set-up | `$000F` (dead time?), `$0FFF`, `$0000` | [C][H] |
| `$3037–$303C` | **6 PWM compare registers** = 2 motors × 3 phases | all set to `500` = 50 % of the period (zero voltage) at start; updated by the IRQ1 handler | [C][I] |
| `$303F` | ASIC status | bits 2–5 (`$003C`) read into the status word | [C] |
| `$3200` | output latch (write-only) | status word `$38BD`; bit 7 toggles every `$2000` cycles → **heartbeat LED** | [C][I] |
| `$3400` | **AD7874** data port | 4 consecutive reads = channels 1–4 after each conversion | [C][I] |
| `$1000`, `$1001` | 2× 8-bit outputs (DAC?) | two variables picked by pointer + gain (`$38A8/9`, `$38AC/D`), written every current-loop cycle → probably **analog monitor outputs** | [C][H] |
| `$3800–$39FF` | internal DM | variables, filter state, parameter tables | [C] |

All the `$30xx` registers sit in one 64-word block and each DSP has its own CXD8501R.
So the CXD8501R most likely contains the host mailbox, the 6-channel PWM and the
status/ID inputs. [I]

## 5. Interrupts and control flow (page 1)

| Vector | Enabled | Handler | Role |
|---|---|---|---|
| RESET `$0000` | — | `SYSCNTL=$101A`, init → `loc_0014` | PWM to 50 %, mailbox clear, read module IDs (`$3030`), load per-type constants, enable IRQs, main loop at `loc_0041` [C] |
| IRQ2 `$0004` | yes | `→ loc_015F` | **status/supervision cycle**: reads `$3030`, checks driver ready bits, manages enable/fault bits in `$3021–$3023`, sets/resets FLAG_OUT, publishes status, runs per-motor control steps (`sub_025B`, `sub_0118`), heartbeat → `$3200` [C][I] |
| SPORT0 RX `$000C` | yes | `JUMP (I4)` with I4 = `DM($38D2)` | **serial link state machine**: the next-state address is kept in `$38D2` (`$0389`, `$039A`, `$03EA` …) [C] |
| IRQ1 `$0010` | yes | `→ loc_0128` (I1 = `$3400`) | **current loop**: 4 ADC reads, filtering (`sub_02A0`), controller (`sub_02F5`, `sub_02FF`), new PWM compares to `$3037…`, monitor DAC `$1000/$1001` [C][I] |

**Host commands** (main loop, command word at mailbox `$3000`): [C][I]

| Command | Action |
|---|---|
| `$Cxxx` | **peek**: 12-bit field, `$000–$7FF` = PM `$000–$7FF`, `$800–$FFF` = DM `$3800–$3FFF` → reply in `$3001` |
| `$Dxxx` | **poke**: write the data word to DM/PM. The word must equal the current `$3001`, a consistency check against the copy taken at loop start |
| `$8001` | **enable** request: clears `$3022`; unless FLAG_IN is set, writes `7` to `$3023` and checks the driver ready bits in `$3030`; then `6` to `$3023`, checks `$3021`/`$3022`, acknowledges |
| `$8082`, `$8084` | not handled by the main loop (no ack there). The **IRQ2** path (`loc_01E2`, mask `$FFEF`) starts the SPORT0 state machine and acks (`$3000 = 0`) when it finishes → **serial absolute-encoder read** for motor A / B (SERVO monitor `ABSCOPY`). See `doc/servo_dsp_link.md` |
| `$8000`, `$8002`, `$8004`, `$8006`, `$9002` | **mode** commands: `cmd − $8000` (0, 2, 4, 6, `$1002`) is stored in `$3800`. Bits 1 and 2 enable motor A / motor B of the pair (the state of a disabled motor is cleared). FLAG_OUT is set while either is enabled |

**Entering page 2.** `loc_03EB` checks for the magic pair `$4123`, `$1002` in DM
`$3832/$3833` (no code in page 1 writes them, so presumably the host writes them with the poke command). `$1002` is also the stored value of mode command `$9002`. If found, it sets `$3025=$000F` and
`$3033=$0FFF`, masks all interrupts and reboots with `SYSCNTL=$0298` (BPAGE 2, BFORCE). [C]

**Page 2 (ADC measurement mode).** IRQ1 → four AD7874 reads. Each channel goes through a
32-sample moving sum ×`$0800`, using buffers at `$3800/$3820/$3840/$3860`. Raw and filtered
values are written to the mailbox `$3000–$3007`, and the last SPORT0 RX word to `$3009`.
`$0080` is written to `$3025` to start the next conversion. The main loop is just
`IDLE`. This looks like a current-sensor **offset/calibration** mode driven by the SERVO
board. [C][I]

## 6. What the code says about feedback

*Revised after the SERVO side was found (`doc/servo_dsp_link.md`).*

- The DSP runs the **current (torque) loop**: phase currents from the AD7874, PWM out,
  driver module IDs/ready bits from `$3030`. Position and speed loops are on the SERVO
  board's V810. [C][I]
- **SPORT0 is most likely the serial absolute-encoder link.** The DSP is the clock master
  and sends 16-bit frames. The SERVO board triggers a read per motor with `$8082`/`$8084`
  (its monitor command `ABSCOPY (axis) -> UPDATE COUNTER FROM SERIAL ABS`), and the DSP
  acks when the SPORT0 state machine finishes. [I]
- Incremental position is probably counted in the CXD8501R (`$3029`/`$302D`, read twice for
  a stable value by the DSP and read per axis by the SERVO board). [H]
- So the encoder lines most likely **end at the Control board**. The earlier
  "pass-through to SERVO" guess is withdrawn. [H]

## 7. Tool limits (`tools/adsp/adsp21xx.py`)

- Linear sweep: **data tables in PM are disassembled as code.** Known data areas: page 0
  `$0084–$00BF` (parameter tables: `$0089` per-strap table, `$0092` 24 words → DM `$381A`,
  `$00AA` 5 words → `$3838`, `$00AF` 12 words → `$3858`); page 1 `$032D–$036A` (filter and
  parameter tables, e.g. the false `DM($0000)` reads at `$0331`); page 1 `$03FB–$03FF`.
- I-register tracking covers straight-line code and one-instruction `DO` loops. It resets
  at branch targets, so addresses inside longer loops show the first iteration only.
- The interrupt-vector labels apply only to pages that use them as vectors. Page 0 runs
  straight through the vector area.

## 8. Next steps

1. Mark the PM data areas in the tool (a simple `--data` list per page) and print them
   as tables.
2. Follow the IRQ1 path (`sub_02A0`, `sub_02F5`, `sub_02FF`): filter coefficients, PI gains,
   current scaling per module type.
3. ~~Match the mailbox with the SERVO side~~ — done: `doc/servo_dsp_link.md` (window
   `0x400000`/`0x400080`, commands `$8001`, `$8000–$8006`, `$8082/$8084`, pokes `$D8A8–$D8AB`).
4. Decode the SPORT0 state machine (`$0389`, `$039A`, `$03EA`) as the serial ABS frame and
   find where the result lands (`$3009`/`$300B`?).
5. Hardware: continuity-test the feedback connector → Control board → 50-pin cable.
