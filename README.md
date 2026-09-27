# Sony SRX-611 — Reverse Engineering

Static reverse engineering of the **Sony SRX-611 SCARA robot** and its controller/board
firmware (IDA Pro, Ghidra, capstone/Python). This repository collects the extracted
firmware images, the IDA databases, the original PC host tools, analysis reports and
helper scripts.

![Sony SRX-611 SCARA robot](img/main.jpg)

> Agent/work context and per-address details live in [`AGENTS.md`](AGENTS.md).

---

## 1. The robot (from the SRX-611 Operation Manual)

The **SRX-611** is a member of the **Sony SRX-600 high-speed assembly robot series** — a
SCARA robot for small-parts assembly, inspection and handling. It uses brushless AC
servo motors with **absolute encoders** (battery-backed), so it is maintenance-free and
needs no home return in normal use.

- **Kinematics:** SCARA, **4 axes** (X, Y, Z, R).
- **Drive:** all-axis AC servo, **software servo** (manual wording). The unit studied here
  has **four physically separate servo controller boards**, one per axis. Each has a
  NEC V810 CPU and is linked to the main CPU through dual-port RAM (see §3.1).
- **Position detection:** absolute method, battery back-up.
- **Programming language:** **LUNA** (Ver. 5.0), compiled on DOS (≥ 5.0), debugged from
  Windows with the SRX Platform kit; teaching via the optional teaching pendant.
- **Controller:** **SRX-C61** — see control specifications below.
- **Multi-task:** 16 LUNA tasks (8 robot + 8 peripheral) + 1 system task + 1 PLC task
  (18 total), plus a Boolean-algebra **PLC** engine sharing the robot's I/O.
- **Safety / SMART option:** the SMART variant adds a hardware **Drive Safety Switch
  (DSS)** (`DSS0`/`DSS1` on the safety connector) and an over-speed detector (SPD panel
  board).
- **Error reporting:** numeric codes `E nnn` (`E000…E400` in the manual) shown on the
  teaching pendant; the later SMART firmware adds **`E401 DSS off error`**.

### 1.1 Unit specifications — SRX-611 (L6015)

| Item | Value |
|---|---|
| Total arm length | 600 mm (1st arm 350 mm, 2nd arm 250 mm) |
| Z axis stroke | 150 mm |
| R axis range | 360° |
| Payload | 2 kg / 3 kg / 5 kg (4.4 / 6.6 / 11 lbs.) |
| Cycle time | 0.6 s (2 kg payload) |
| Max speed | arms 5200 mm/s, Z 770 mm/s, R 1150°/s |
| Pose-repeatability | X-Y 0.01 mm, Z 0.02 mm, R 0.03° |
| Weight | 35 kg (77 lbs.) |
| Tool items | 15 signal wires, 3 air ducts |

**Model variants:** `L4015` (400 mm, arms 200/200), `L8015` (800 mm, arms 450/350),
and long-Z versions `L**45` (Z stroke 450 mm).

### 1.2 Controller specifications — SRX-C61

| Item | Value |
|---|---|
| CPU | **Intel i486DX2 (50 MHz internal)** |
| Drive / axes | AC servo, software servo; simultaneous & individual control of axes 1–4 |
| Motion | PTP, CP, overlap motion, QM, QT; 3-D linear and 3-D circular interpolation |
| Speed control | 1–100 % in 100 steps, override 1–100 % |
| Output | motor power total max 1000 W |
| Program storage | 3072 points per program, 176 kB total across all tasks |
| Memory card | PC Card (PCMCIA 2.1 Type 1) |
| Serial I/F | RS-232C × 3 (teaching pendant, programming device, general purpose); in firmware these are three 8251A USARTs, ch 1/2/3 |
| Expansion | 3 slots (vision board, I/O board, …); the firmware scans **5 slot windows** shared by servo and I/O boards |
| Power | single-phase AC 200–240 V ±10 %, 50/60 Hz, 1.5 kVA |
| Dimensions / weight | 430 (w) × 440 (d) × 240.5 (h) mm ≈ 5U DIN; 25 kg |
| Environment | 0–40 °C, 35–90 % RH (non-condensing) |

---

## 2. Firmware / binaries

All paths are relative to the project root.

| Firmware | Files | Device | Target CPU | Description | Research status |
|---|---|---|---|---|---|
| **CPU main firmware** | `FW/SRX6-CPU/2/ROM1-C.bin` (1 MB) | 2× **MT28F400B5** flash, U24+U25, 512 KB each | **Intel 80486** (32-bit flat protected mode) | RTOS **pSOS+/386 V2.0.I** (Integrated Systems) + robot application + **LUNA** interpreter | **In progress — primary target.** IDA DB `ROM1-C.bin.i64`, 1298 annotated functions, architecture & error reports, partial C decompilation |
| **CPU boot EPROM** | `FW/SRX6-CPU/2/U23_M27C256B@DIP28.BIN`, `FW/SRX6-CPU/1/U26_….BIN`, `FW/SRX6-CPU/M27C256B@DIP28.BIN` (all identical) | **M27C256B**, 32 KB | Intel 80486 | Boot/monitor EPROM, separate from the main image | Preliminary — IDA DBs (`80486r`) exist |
| **Teach pendant (TP)** | `FW/TP/IC6_M27C256B@DIP28.BIN` (32 KB) | **M27C256B** | **Hitachi HD64180/Z180** | Thin terminal: keypad, 20-char display, serial command interpreter | **Analysed** — see [`doc/TP_firmware_structure.md`](doc/TP_firmware_structure.md) |
| **Servo board** | `FW/SRX6-SERVO/ROM_SERVO.bin` (256 KB); sources `1/U41_P28F010@DIP32.HEX`, `1/U42_P28F010@DIP32.BIN`; PLD `2/U43.GAL16V8B.JED` | 2× **P28F010**, U41+U42, 128 KB each (byte-interleaved: U41 = even bytes) | **NEC V810 (µPD70732)**, 16-bit bus | Servo board firmware ("Servo Board Monitor ©1995 Sony"); talks to the CPU board through a slot dual-port RAM | IDA DB `ROM_SERVO.bin.i64` exists; CPU identified, not written up |
| **Servo-I/O board** | `FW/SERVO_IO/1/U7_M27C512@DIP28.BIN`, `FW/SERVO_IO/1/U18_M27C512@DIP28.BIN` (64 KB each) | 2× **M27C512** | unconfirmed (V810 guessed) | Servo-I/O controller pair (no ASCII strings in the dumps) | Not started |
| **PC-side tools (SRXWIN)** | `SRXWIN/*.EXE`, `SRXWIN/SRXMONIE.HLP` (19 files, MD5-verified) | — | x86 DOS / Win16 host PC | Sony host toolchain (1991–1996): `LUNNA`/`POINT`/`PLC` compilers, `ANNUL`/`DISPON`/`DPLC` decompilers, `SEND`/`RECALL`/`FILES`/`FDEL`/`HIST`/`MONIT`, `INI_RS`, `LUNAPR`, MFC "SRX Platform" GUI `SRXMONIE`, installer | **Analysed** — structure, serial protocol, LUNA/PLC token tables, help text (see §3.2); replacement spec [`doc/SRXWIN-NG.md`](doc/SRXWIN-NG.md) |

Component datasheets, manuals and design files (SRX operation manual, user training
manual, SPD panel board, 486DX2/DX4, M27C256B, Altera MAX 7000, NEC µPD70732/V810, …)
are listed in [`AGENTS.md`](AGENTS.md) §2.7. The operation manual is in [`books/`](books).

---

## 3. Research status

Research **started with the CPU-board firmware** (`ROM1-C.bin`), which is the core of the
controller, and is the most advanced track. The other boards have only raw dumps and/or
preliminary IDA databases.

### 3.1 CPU firmware (`ROM1-C.bin`) — done so far

- Full disassembly/annotation in IDA Pro 9.0 (`ROM1-C.bin.i64`): **1298 functions**
  named by category, each with a call-popularity comment;
  [`function_popularity.md`](doc/function_popularity.md).
- Platform established: 80486 in flat 32-bit protected mode, runtime base
  `0xFFE00000 + file offset`, RTOS **pSOS+/386 V2.0.I** (`int 90h` kernel calls,
  `int 91h` I/O supervisor).
- **Hardware interfaces mapped** (architecture report v2, 2026-09-26):
  - three 8251A USARTs: ch 1 = **teach pendant** (ESC frames without a checksum,
    `SRX6`↔`TP4` handshake, 38 commands), ch 2 = **PC host** (SRXWIN protocol), ch 3 =
    **user RS-232C** (LUNA `READ/WRITE/RS*`);
  - 8259A PIC pair, 8254 timer (10 ms tick and baud clocks);
  - **five slot dual-port-RAM windows** (`0x700000 + n·0x10000`) for servo and I/O
    boards, each with its own IRQ. The per-robot servo task runs once per servo-board
    interrupt: it reads feedback, runs the motion and the **PLC scan**, and writes the
    references back;
  - RTC, 8 KB EEPROM, PC-card window, optional 4-port serial board.
- **Software structure:** pSOS+ task model (INIT, SYST, TPCT, PCCT, PLCT, SVTn, TJTn,
  LTnn LUNA tasks, ERRT, …), 5 device drivers, the LUNA statement-executor table, and the
  error path.
- **Strings are used from RAM.** Boot copies all strings and their pointer tables from ROM to
  RAM, which explains the missing string xrefs. The RAM image is rebuilt with
  [`tools/cpu/rom1c_raminit.py`](tools/cpu/rom1c_raminit.py).
- Also mapped: config validation, PLC engine, motion/point, teach-pendant UI, LUNA language.
  Several v1/IDA names turned out wrong (e.g. `db_access` = TP link, `dma8237_init` = USART
  init); the corrections are listed in the architecture report §2.
- **Error system analysed**: full `E000…E401` message table; identified
  **`E401 = DSS off error`** (SMART) —
  [`SRX-611_error_401_DSS_report.md`](doc/SRX-611_error_401_DSS_report.md).
- Architecture report v2 with diagrams, interface details and corrections to v1:
  [`SRX-611_firmware_architecture.md`](doc/SRX-611_firmware_architecture.md).
- Partial C decompilation (Hex-Rays): `FW/SRX6-CPU/2/c_decomp/` (top-50 functions) and
  `FW/SRX6-CPU/2/c_decomp_luna/` (LUNA subsystem, 43 functions +
  [`LUNA_analysis.md`](doc/LUNA_analysis.md)).

### 3.2 PC-side tools (`SRXWIN`) — done so far

- Inventory, provenance, toolchain (Borland C++ DOS suite + 1996 MSVC/MFC GUI) and MD5s
  of all 19 files; how the GUI drives the DOS compilers via `.PIF`.
- File-format map (`.LUN/.OBJ`, `.PON/.DAT/.CDT/.MDT`, `.PLC/.COD`, `.CTR`, `.KEE`, `.HST`, …)
  and serial-line hypotheses (`9600,n,8,2`, DSR, ESC-code session start, checksum).
- Cross-links to the firmware (LUNA/PLC keyword tables, PLC relays, error sets) —
  [`SRXWIN_tools_report.md`](doc/SRXWIN_tools_report.md).
- Spec for a modern cross-platform replacement, **SRXWIN-NG** (RU) —
  [`SRXWIN-NG.md`](doc/SRXWIN-NG.md).
- **Serial protocol** reversed from the DOS utilities: 9600 8N2 with DTR/RTS/DSR, ESC frames
  `1B LEN CMD … SUM`, commands for download/upload/directory/delete/error history, and status
  codes = E4000+s. Also a catalog of the ~110 SRX Platform monitoring commands —
  [`SRXWIN_protocol.md`](doc/SRXWIN_protocol.md).
- **LUNA symbol table** (230 keywords with token codes) recovered from `LUNNA.EXE` and
  cross-checked with the `ANNUL.EXE` decompiler. The firmware table at `0xD99D2` turned out to
  be the **PLC** mnemonic table — [`LUNA_token_map.md`](doc/LUNA_token_map.md).
- **Help file** `SRXMONIE.HLP` fully extracted (333 topics: LUNA/PLC command reference, GUI,
  error codes) — [`SRXMONIE_help.md`](doc/SRXMONIE_help.md). Extractors are in
  [`tools/srxwin/`](tools/srxwin).
- **Controller side of the protocol** located in `ROM1-C.bin`: the command-server task, the
  frame reader (its status codes match the host tables) and a 172-entry handler table
  (`SRXWIN_protocol.md` §9). A Ghidra project with the ROM at its link address `0xFFE00000`
  can be recreated with [`tools/ghidra/`](tools/ghidra).

### 3.3 Planned / remaining

- Complete the CPU-firmware decompilation (several switch-heavy functions must be
  hand-reconstructed; see `AGENTS.md` §8). Apply the v2 function names to the IDA DB.
- Confirm on the real unit which slots hold the four servo controllers, and what is in
  slot 5.
- Servo board: document `ROM_SERVO.bin` (V810, code at `0x00100000`): monitor console,
  amplifier diagnostics, and its side of the dual-port-RAM protocol (meaning of the
  per-axis fields).
- Servo-I/O board: load `U7`/`U18` into IDA and identify the CPU.
- PC tools (`SRXWIN`): name the SRX Platform monitoring commands, decode the LUNA `.OBJ`
  statement encoding, and confirm the protocol on hardware (SRXWIN-NG stage 1).
- Name the 152 controller-side command handlers (the server task and table were found at
  `0x50D00`/`0x51828`) and label `token_dispatch` with the LUNA token codes.
- Teach pendant: confirm the TP commands still marked as hypotheses (architecture report
  §8.1).
- Servo-I/O board: find out how it connects to the CPU board (slot I/O board or not).

---

## 4. Documentation

Detailed analysis notes are collected in [`doc/`](doc):

| Document | Contents |
|---|---|
| [`SRX-611_firmware_architecture.md`](doc/SRX-611_firmware_architecture.md) | CPU-firmware architecture report v2: pSOS+ kernel/BSP, drivers, IRQ/port/memory maps, tasks, TP / PC / RS-232C / servo-DPRAM interfaces (mermaid diagrams) |
| [`SRX-611_error_401_DSS_report.md`](doc/SRX-611_error_401_DSS_report.md) | Error-reporting system + full `E000…E401` analysis; `E401 = DSS off` |
| [`TP_firmware_structure.md`](doc/TP_firmware_structure.md) | Teach-pendant (HD64180) memory map, command dispatcher, `"SRX6"`↔`"TP4"` handshake |
| [`LUNA_analysis.md`](doc/LUNA_analysis.md) | LUNA language subsystem analysis (companion to `FW/SRX6-CPU/2/c_decomp_luna/`) |
| [`function_popularity.md`](doc/function_popularity.md) | All 1298 CPU functions ranked by call popularity + comments |
| [`SRXWIN_tools_report.md`](doc/SRXWIN_tools_report.md) | PC-side host toolchain (`SRXWIN`): LUNA/POINT/PLC compilers & decompilers, SEND/RECALL/FILES/FDEL/HIST/MONIT, `INI_RS`, `LUNAPR`, MFC "SRX Platform" GUI (`SRXMONIE`), installer, formats, serial protocol |
| [`SRXWIN-NG.md`](doc/SRXWIN-NG.md) | (RU) Spec for SRXWIN-NG, a modern replacement toolchain: architecture, requirements, stages, roles, hardware-safety rules |
| [`SRXWIN_protocol.md`](doc/SRXWIN_protocol.md) | PC↔controller RS-232 protocol: line settings, framing/checksum, commands, status codes, SRX Platform command catalog, DOSBox-X oracle confirmation (§10) |
| [`srxwin-ng/README.md`](srxwin-ng/README.md) | SRXWIN-NG code: `srx` CLI, fake controller, DOSBox-X oracle/golden runner; specs in [`srxwin-ng/docs/spec/`](srxwin-ng/docs/spec) |
| [`LUNA_token_map.md`](doc/LUNA_token_map.md) | LUNA keyword/token table (from `LUNNA.EXE`), ANNUL cross-check, PLC mnemonic table |
| [`SRXMONIE_help.md`](doc/SRXMONIE_help.md) | Full extracted text of `SRXMONIE.HLP` (LUNA/PLC reference, GUI, error codes) |

The project-wide agent context and per-address reference is [`AGENTS.md`](AGENTS.md);
the per-session work log is [`history.md`](history.md).

### 4.1 Tools

| Path | Purpose |
|---|---|
| [`tools/cpu/rom1c_raminit.py`](tools/cpu/rom1c_raminit.py) | Rebuild the CPU firmware's initial RAM image; find a string's RAM address (`--find`) and pointer tables (`--ptr`) |
| [`tools/ghidra/`](tools/ghidra) | Headless Ghidra: import `ROM1-C.bin` at `0xFFE00000`, seed functions, label the host protocol, print decompiled C (heavy on a small machine) |
| [`tools/ida/rebase_ffe00000.py`](tools/ida/rebase_ffe00000.py) | IDAPython: rebase `ROM1-C.bin.i64` to `0xFFE00000` so the jump tables resolve (run on a copy) |
| [`srxwin-ng/`](srxwin-ng) | SRXWIN-NG (Python): `srx` CLI (files/send/recall/hist/backup/delete/compile), `srx-fake` controller emulator, DOSBox-X harness |
| [`tools/srxwin/`](tools/srxwin) | SRXWIN helpers: WinHelp extractor, LUNA symbol-table dumper, SRXMONIE command scanner |
