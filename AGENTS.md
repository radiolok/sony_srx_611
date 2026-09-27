# AGENTS.md — Sony SRX-611 reverse engineering

Context file for AI coding agents working anywhere in this project.

- **Repository root:** the git checkout that holds this file. All paths below are
  **relative to the repo root** and written with `/`.
- **Main analysis workdir (CPU-board firmware):** `FW/SRX6-CPU/2/`.
- **Original workstation** (Windows, where IDA Pro runs and where the full, un-versioned
  material lives): `D:\radiolok@oc.urlnn.ru\Datasheets\SONY SRX`. Some of what this file
  mentions exists **only there**, not in git (see §2.7).

## 0. Working rules (from the project owner)

1. **Record every investigation as Markdown.** Write new findings to a report in `doc/`
   or extend the existing one. Don't leave results only in chat.
2. **Append to `history.md` every session.** Add one bullet of 1–2 sentences saying
   what the session did. Example:
   `- Made SRXWIN analysis, saved doc/SRXWIN_tools_report.md.`
3. **Keep this file current.** When the user brings new data (dumps, documents, tools)
   or a finding changes a fact, update the relevant section here and add new docs to
   the `README.md` §4 table.
4. **Ask when unsure.** If you are not sure about an idea, interpretation or direction,
   ask the user instead of deciding on your own.
5. **Take care of machine resources.** The project may run on small nodes. Prefer light
   tools (Python, capstone) over heavy ones (full Ghidra analysis, decompile-all), and ask
   the user before starting any long-running heavy job.

## 1. What this project is

This project reverse-engineers the **Sony SRX-611 SCARA robot controller** and its
surrounding boards, mainly by static analysis in IDA. The main focus is the
**CPU-board firmware**: its OS, the robot application, the **LUNA** robot-programming
language, and annotation of the IDA database. The other boards' firmware (servo,
servo-I/O, teach pendant) and the PC-side host tooling (SRXWIN) are summarised in §2.
That lets an agent place any binary it is asked about before reading the detailed
CPU-board notes in §3–§11.

A follow-on project, **SRXWIN-NG**, is specified in `doc/SRXWIN-NG.md` (Russian). It is
a modern cross-platform replacement for the 16-bit SRXWIN host tools (§2.5).

## 2. Firmware / binary inventory (all boards)

| Board / image | Location | Device(s) | CPU / bus | What it is | Analysis state |
|---|---|---|---|---|---|
| CPU main firmware `ROM1-C.bin` | `FW/SRX6-CPU/2/` | 2× MT28F400B5 flash (U24+U25), 512 KB each | Intel 80486, **32-bit** code linked at `0xFFE00000` (see §4) | 1 MB controller OS + robot application (the main target) | **Fully annotated**: `ROM1-C.bin.i64`, reports in `doc/` (§3) |
| CPU boot EPROM | `FW/SRX6-CPU/2/U23_M27C256B@DIP28.BIN`, `FW/SRX6-CPU/1/U26_M27C256B@DIP28.BIN`, `FW/SRX6-CPU/M27C256B@DIP28.BIN` | M27C256B, 32 KB | Intel 80486 (real mode) | Boot/monitor EPROM, separate from the main image. All three files are the **same image** (MD5 `ad0652d1fbf4c19faebd26b2250d2e33`) | IDA DBs only (proc `80486r`): `FW/SRX6-CPU/1/U26_….i64`, plus unpacked `.id0/.id1/.nam/.til` next to `FW/SRX6-CPU/M27C256B@DIP28.BIN`. Not written up |
| Teach pendant (TP) EPROM | `FW/TP/IC6_M27C256B@DIP28.BIN` | M27C256B, 32 KB | Hitachi **HD64180/Z180** | Thin terminal: keypad, 20-char display, serial command interpreter | **Analysed**: DB `IC6_….i64`, report `doc/TP_firmware_structure.md` (§2.2) |
| Servo board `ROM_SERVO.bin` | `FW/SRX6-SERVO/` | 2× P28F010 flash (U41+U42), 128 KB each | 16-bit bus (byte-interleaved) | Servo amplifier/monitor firmware. `ROM_SERVO.bin` (256 KB) = U41 even bytes + U42 odd bytes | IDA DB `ROM_SERVO.bin.i64` exists; no write-up yet |
| Servo-board PLD | `FW/SRX6-SERVO/2/U43.GAL16V8B.JED` | GAL16V8B | — | Glue logic / address decode JEDEC | Raw dump only |
| Servo-I/O board EPROMs | `FW/SERVO_IO/1/U7_M27C512@DIP28.BIN`, `FW/SERVO_IO/1/U18_M27C512@DIP28.BIN` | 2× M27C512, 64 KB each | 32-bit RISC (likely NEC µPD70732 / V810) | Servo-I/O controller pair (128 KB total). **No ASCII strings** in the raw dumps | Not analysed |
| PC-side tools (SRXWIN) | `SRXWIN/` (19 files, MD5-verified against the tools report) | — (x86 DOS / Win16) | host PC | Sony host toolchain: LUNA/POINT/PLC compilers and decompilers, serial utilities, and the "SRX Platform" MFC GUI | **Analysed**: structure (`doc/SRXWIN_tools_report.md`), serial protocol (`doc/SRXWIN_protocol.md`), LUNA/PLC tokens (`doc/LUNA_token_map.md`), help text (`doc/SRXMONIE_help.md`). Replacement spec: `doc/SRXWIN-NG.md` |

### 2.1 CPU board (SRX6-CPU) — main controller

- **Main firmware** = the 1 MB image `ROM1-C.bin`, built from the two 512 KB
  `MT28F400B5` flash devices **U24** and **U25** (TSOP48). All of §3–§11 refers to
  this image.
  - A raw byte concatenation or byte-interleave of the U24/U25 dumps does **not**
    reproduce `ROM1-C.bin` (verified). Treat `ROM1-C.bin` as the authoritative image.
- **Boot EPROM** = 32 KB `M27C256B` (socket U23 / U26), a separate x86 real-mode image.
  All three on-disk copies are identical (see the table).
- CPU is an Intel/IBM 80486. The manual gives i486DX2 at 50 MHz internal (see
  `README.md` §1.2).

### 2.2 Teach pendant (TP)

- 32 KB `M27C256B` (socket IC6) running a Hitachi **HD64180** (Z180/Z80-compatible) in
  IM2 mode, with ASCI serial.
- Only about `0x205A` bytes of the ROM are used, in 121 functions. The TP holds **no
  robot logic and no error text**: the CPU board formats all text. Handshake: the CPU
  sends `"SRX6"` and the TP replies `"TP4"`.
- Full report: `doc/TP_firmware_structure.md`.

### 2.3 Servo board (SRX6-SERVO)

- Two P28F010 flash devices (`1/U41_P28F010@DIP32.HEX` + `1/U42_P28F010@DIP32.BIN`,
  128 KB each) form a 16-bit bus: **U41 = even/low bytes, U42 = odd/high bytes**. Together
  they make `ROM_SERVO.bin` (256 KB).
- `2/U43.GAL16V8B.JED` is a GAL16V8B PLD.
- Strings in the firmware identify a **"Servo Board Monitor / Copyright(C) 1995 Sony
  Corp."** serial console (`VER`, `CONNECT`, `ABSCOPY`, `HELP`). It includes amplifier
  diagnostics (`AMP ERROR(axis 1/2): watch dog|hardware|software|initialize`) and a full
  servo/amp error list, and references **SRX-610** and **SRX-630(FEB)**.
- **CPU = NEC V810 (µPD70732)** (confirmed 2026-09-26): the reset vector at `0x3FFF0` is
  `movhi 0x10,r0,r31; jmp [r31]`, and the interrupt slots hold V810 `jr` instructions.
  The code starts at `0x00100000`.
- It talks to the CPU board through a **dual-port-RAM slot window** (see
  `doc/SRX-611_firmware_architecture.md` §8.4). The monitor has `MODE (L/R)` and `RMTCMD`,
  and error texts `host CPU communication error` / `host CPU watch dog timer error`.
- The owner reports **four physically separate servo controllers** (one per axis). The CPU
  firmware supports 5 slots; the axis → (slot, sub-axis) map is the SLOT/AXIS setting.

### 2.4 Servo-I/O board (SERVO_IO)

- Two 64 KB `M27C512` EPROMs (`U7`, `U18`) give 128 KB of program space. The raw dumps
  contain **no printable ASCII strings** (code and numeric data only), so no banner has
  been recovered.
- The CPU is unconfirmed; V810 is a guess (the servo board, §2.3, is a confirmed V810). The
  images have not been loaded into IDA yet. The CPU board sees I/O boards as **slot kind 3**
  (architecture report §8.4); whether this board is one of them is unknown.

### 2.5 PC-side tools (SRXWIN) — see `doc/SRXWIN_tools_report.md`

- **Binaries are in `SRXWIN/`** (added 2026-09-26). All 19 files match the MD5s in the
  report's §8. `SRXWIN.zip` itself is not versioned.
- Deep-dive reports: `doc/SRXWIN_protocol.md` (wire protocol), `doc/LUNA_token_map.md`
  (keyword/token tables) and `doc/SRXMONIE_help.md` (all 333 help topics as text).
- Era 1991–1996. A **Borland C++ DOS** suite, built from an internal Sony tree
  `C:\L50\…`, wrapped by a 1996 **MSVC/MFC Win16** GUI.
  - Compilers: `LUNNA.EXE` (LUNA 5.0 compiler v1.05, `.LUN`→`.OBJ`), `POINT.EXE`
    (`.PON`→`.DAT/.CDT/.MDT`) and `PLC.EXE` (`.PLC`→`.COD`, ≤ 32 KB).
  - Decompilers: `ANNUL.EXE` (`.OBJ`→`.LUN`), `DISPON.EXE` (points) and `DPLC.EXE`
    (PLC).
  - Serial utilities: `SEND`, `RECALL`, `FILES`, `FDEL`, `HIST` (error history, `.HST`),
    `MONIT`, and `INI_RS` / `INI_RS98` (port init; `INI_RS98` is for the PC-98). They
    share a common `rsfnc.c` / `messg.c` module.
  - `LUNAPR.EXE`: a 1991 Turbo C++ listing printer.
  - `SRXMONIE.EXE`: the "SRX Platform" GUI. It shells out to the DOS tools through
    `.PIF` files and holds its settings in `SRXWIN.INI`.
  - `SRXMONIE.HLP`: the full help and command reference (WinHelp 3.1, 333 topics): LUNA and
    PLC command reference, GUI, error list E000–E382 and E4001–E4408. It does **not**
    contain E400/E401 (no DSS/SPD text).
  - `INSTALLE.EXE`: the installer.
- **Serial protocol** (from static disassembly; not yet confirmed on hardware), see
  `doc/SRXWIN_protocol.md`:
  - Line: COM1/COM2, **9600 8N2**. The host raises DTR/RTS and sends only while DSR is high.
  - Frames: `1B LEN CMD args… SUM`, where LEN is the whole frame length and SUM is the
    8-bit sum of the preceding bytes. Reply: `1B LEN xx STATUS payload… SUM`; status s ≠ 0
    is reported by the GUI as **E(4000+s)**.
  - DOS-tool commands: `01`/`02` download (≤ 128-byte blocks), `04` upload, `05`
    directory, `06` delete, `14`/`15` error history. SRXMONIE uses ~110 commands
    (`01`–`A6`) for online monitoring; their names are not resolved yet.
  - Kind byte: `5A` .CDT, `5B` .CTR, `5C` .OBJ, `5D` .DAT, `5E` .COD, `5F` system program
    (type 100).
  - `MONIT.EXE` is a plain ASCII terminal on the same port (the controller also has a text
    monitor).
- Program type numbers: LUNA 0–89 and 100–180 (the DOS tools use 0–15), PLC 90–93,
  system program 100. Compiler error codes: LUNA 2000–2089, POINT 2092–2133,
  PLC 3115–3120.
- Cross-links to the firmware:
  - **`LUNNA.EXE` holds the full LUNA symbol table** (230 × 15-byte records @file
    `0x135E4`). Token rule: if group `d3 = 0` the token is `d2`, otherwise the token is
    `d3` and `d2` is the sub-index. Cross-checked with ANNUL. Use it for the LUNA
    `token_dispatch` decode (§8.2); see `doc/LUNA_token_map.md`.
  - The firmware table at `0xD99D2` is the **PLC** mnemonic table (same content and order
    as `DPLC.EXE`), not a LUNA one.
  - PLC special relays map to `plc_scan` / `plc_program_exec`.
  - `HIST.EXE` carries a 600-slot E-code text table with 121 entries (E000–E390). It is a
    subset of the firmware's table; the firmware adds 17 newer messages, including E400
    and E401.
- File formats: `.LUN/.LSF/.OBJ/.LIB`, `.PON/.CPN/.MPN` → `.DAT/.CDT/.MDT`,
  `.PLC/.COD`, `.CTR` (robot parameters), `.KEE` (keep relays), `.HST`. The full map is
  in the report's §4.

### 2.6 SRXWIN-NG (planned replacement toolchain) — `doc/SRXWIN-NG.md`

- The spec is written in **Russian**. Its deliverables are `srx-link` (RS-232 protocol
  library), `srx-cli` (SEND/RECALL/FILES/FDEL/HIST/MONIT equivalents), `srx-lang`
  (LUNA/POINT/PLC compilers and decompilers, byte-exact with the originals) and
  `srx-studio` (GUI).
- The plan uses **Ghidra** for the SRXWIN EXEs and **DOSBox-X / 86Box** to run the
  original tools as a protocol oracle.
- **Hardware safety rules (spec §8) are binding** for anything that talks to a real
  controller:
  - READ, WRITE and MOTION operation classes.
  - No protocol fuzzing against real hardware.
  - Writing `.CTR` and `.KEE` is blocked.
  - Take a full backup before the first connection.
- Open questions are in the spec's §8.3.
- **Code: `srxwin-ng/`** (started 2026-09-27; see `srxwin-ng/README.md`). It is a Python
  3.12+ package in a venv at `srxwin-ng/.venv`, tested with
  `.venv/bin/python -m pytest`, and needs `dosbox-x` (apt).
  - `srx_link` (framing, `Session` with READ/WRITE/MOTION guard + JSONL journal),
    `srx_fake` (fake controller over TCP in DOSBox-X nullmodem format), `srx_dosbox`
    (headless runner + golden runner), `srx_cli` (`srx` command), `srx_formats` (header).
  - Stage 0 and the stage-1 gate are met **without hardware**: the original
    SEND/FILES/RECALL/HIST/FDEL work against `srx-fake`, and `srx_link` sends
    byte-identical frames (`tests/test_dosbox_oracle.py`).
  - CI: `.github/workflows/srxwin-ng.yml` (lint; Linux tests with the DOSBox-X oracle;
    Windows tests without it). It triggers on changes to `srxwin-ng/**` or `SRXWIN/**`.
  - Normative specs are in `srxwin-ng/docs/spec/` (`PROTOCOL.md`, `FORMATS.md`), with
    status tags [H]/[E]/[C]. Nothing is [C] yet.
- **DOSBox-X oracle gotchas:**
  - LUNNA and POINT write to video RAM, so the runner dumps B800 with a tiny
    `SCRDUMP.COM`.
  - Answer `(y/n)` prompts with `< _YES.TXT`.
  - Kill DOSBox-X with SIGKILL (SIGTERM opens a "quit?" prompt).
  - A serial tool with no peer hangs forever.

### 2.7 Support documents and files

**In the repository:**

| Path | Meaning |
|---|---|
| `books/Sony+SRX+Scara+robot.pdf` | SRX operation manual (268 pp). Contains the **Error Code Guide** E000–E400. E401 is absent from it and from `SRXMONIE.HLP`; it is known only from the firmware. |
| `SRXWIN/` | Sony host toolchain binaries (§2.5). |
| `tools/ghidra/` | Ghidra headless setup: `import_rom1c.sh` (project with ROM1-C.bin at `0xFFE00000`), `SeedSrxFunctions.java` (pre-analysis seeding), `LabelSrxProtocol.java` (protocol labels), `DecompileByName.java` (print C). See §7 |
| `tools/ida/` | `rebase_ffe00000.py`: IDAPython script to rebase `ROM1-C.bin.i64` to `0xFFE00000` (run on a copy, on the workstation) |
| `tools/cpu/` | `rom1c_raminit.py`: rebuilds the RAM image from ROM1-C.bin's init stream; finds strings' RAM addresses and pointer tables (§8.1). |
| `srxwin-ng/` | SRXWIN-NG code (§2.6): `srx_link`, `srx_fake`, `srx_dosbox`, `srx_cli`, corpus + goldens, specs in `docs/spec/`. |
| `tools/srxwin/` | Pure-Python helpers: `hlp_extract.py` (WinHelp 3.x → JSON/Markdown), `lunna_symtab.py` (LUNA symbol table), `srxmonie_cmds.py` (protocol frame-builder scan; needs `capstone`). |
| `img/main.jpg` | Photo of the robot (used in `README.md`). |
| `README.md` | Robot and controller specifications, firmware inventory, research status, doc index. |
| `history.md` | Per-session work log (rule §0.2). |
| `doc/` | Analysis reports (§3). |

**Only on the original workstation (not versioned).** Ask the user if you need any of
these:

| Path (workstation project root) | Meaning |
|---|---|
| `37996036.pdf` / `37996036_EN.pdf` | SRX611 user training manual (Tampere 2007 thesis; the EN copy is machine-translated). |
| `SPD Panel Board.odg` / `.pptx`, `SPD_panel_relays.dch` | SPD (speed-detector) panel-board presentation, diagram and relay design. |
| `Intel-80486DX2-66-datasheet.pdf`, `FW\IBM_486DX4.pdf` | CPU-board processor datasheets. |
| `UPD70732GD(A)-25-LBB.pdf` | NEC µPD70732 = V810 32-bit microprocessor (servo-family boards). |
| `FW\M27C256B.pdf`, `FW\MB8432.PDF` (scanned), `FW\SG51PH-50MHZ.pdf` (oscillator), `FW\m7000-1299427.pdf` (Altera MAX 7000 PLD) | Component datasheets. |
| `join_fw.py` | Non-working (malformed) helper meant to join firmware halves (`-l`/`-h`). |
| `FW\SRX6-CPU\2 — копия\` | Backup copy of `FW\SRX6-CPU\2\`. |
| `C:\Users\radiolok\AppData\Local\Temp\kilo\` | IDA scratch scripts/logs and DB backups (§7). |

## 3. Files in the CPU-board workdir (`FW/SRX6-CPU/2/`)

| File | Meaning |
|---|---|
| `ROM1-C.bin` | 1 MB firmware image under analysis (linear image base `0x0`..`0x100000`) |
| `ROM1-C.bin.i64` | IDA Pro 9.0 database (~11 MB). **Packed and self-contained**: it was originally unpacked with `.id0/.id1/.nam/.til` and is now merged. Contains all annotations. |
| `U23_M27C256B@DIP28.BIN` | 32 KB boot EPROM (M27C256B), separate from the main firmware |
| `U24_MT28F400B5-T@TSOP48.BIN` | 512 KB flash |
| `U25_MT28F400B5-T@TSOP48.BIN` | 512 KB flash (U24+U25 = the 1 MB main firmware) |
| `c_decomp/` | C equivalents (Hex-Rays) of the **top-50** functions, one file per name prefix (`app, config, db, disp, flag, format, fpu, int, io, mem, motion, os, plc, record, str, strcpy, sys, token, tp, util, wait`) |
| `c_decomp_luna/` | C equivalents of the **LUNA** subsystem (43 functions; `fn, os, point, token, util`) |

### 3.1 Analysis reports (`doc/`)

| Report | Contents |
|---|---|
| `SRX-611_firmware_architecture.md` | CPU-firmware architecture **v2**: pSOS+/386 kernel + BSP, drivers, IRQ/port/memory maps, task model, TP link (command table), PC link, user RS-232C, slot DPRAM servo channel + servo cycle, RAM-init strings, corrections to v1 |
| `SRX-611_error_401_DSS_report.md` | Error-reporting system, full `E000…E401` analysis; `E401 = DSS off` |
| `TP_firmware_structure.md` | Teach pendant (HD64180) memory map, dispatcher, handshake |
| `LUNA_analysis.md` | LUNA subsystem (companion to `c_decomp_luna/`) |
| `function_popularity.md` | All 1298 CPU functions ranked by call popularity, with comments |
| `SRXWIN_tools_report.md` | PC host toolchain: inventory, architecture, file formats, firmware cross-links, RE leads, MD5s |
| `SRXWIN-NG.md` | (RU) Spec for the modern replacement toolchain: architecture, requirements, stages, roles, hardware-safety rules |
| `SRXWIN_protocol.md` | PC↔controller RS-232 protocol: line settings, frame/checksum, status codes (E4000+s), DOS-tool commands `01 02 04 05 06 14 15`, kind/type addressing, SRXMONIE command catalog, MONIT console, §10 DOSBox-X oracle confirmation |
| `LUNA_token_map.md` | LUNA symbol table from LUNNA.EXE (230 keywords, token codes, groups), ANNUL cross-check, PLC mnemonic table (`0xD99D2` correction) |
| `SRXMONIE_help.md` | Full text of `SRXMONIE.HLP` (generated): LUNA/PLC command reference, GUI, error list |

## 4. Target platform (CPU board, facts)

- **CPU:** Intel 80486 (386-class) with an x87 FPU. IDA processor module: `80486r`.
- **Code model:** the main image is **32-bit code** (`push ebp; mov ebp,esp; …`, 32-bit
  immediates such as `mov edi,461Ch` in `reset_entry`), linked to run at `0xFFE00000`.
  The IDA database already decodes it as 32-bit (see the `c_decomp/*.c` listings). Older
  notes said "16-bit real mode with 32-bit regs"; that is wrong. It runs in **flat 32-bit
  protected mode** (GDT built at `0x5104`, selectors `08`/`10`). The switch into protected
  mode happens in the boot EPROM.
- **OS:** **pSOS+/386 V2.0.I** by Integrated Systems Inc., ©1993 (banner @`0x5B8`, `KC_*`
  config names @`0x60F`). Older notes called it Sony "OS+/386" (the "p" was cut off). The
  kernel is at `0x518`–`~0x3DCB`; the BSP drivers are at `0x3DCC`–`0x6CAB`.
- **Runtime base:** code and data are referenced at **`0xFFE00000 + file_offset`**, so
  file offset = runtime address − `0xFFE00000` (e.g. `0xFFEBFF4C` → file `0xBFF4C`).
- **Syscall ABI:** function code in `EAX`, then `int 90h` (pSOS+ kernel calls:
  `1` t_create, `3` t_start, `24` q_create, `27` **q_send**, `29` q_broadcast, `2A` q_receive,
  `36/37` sm_p/sm_v, `3C` tm_wkafter, …) or `int 91h` (I/O supervisor `1..6` =
  `de_init/open/close/read/write/cntrl`; device = `major<<16|minor`). The wrappers live at
  `0xCDE13`–`0xCE556` and are named `os_syscall_90h_XXh` / `os_syscall_91h_XXh` in IDA. The full
  table is in the architecture report §5.2.
- **Drivers (pSOS majors):**
  - 1 = serial: three **8251A USARTs**, data/ctrl `C0/C4` ch1 = **teach pendant**, `C8/CC` ch2 =
    **PC host**, `D0/D4` ch3 = **user RS-232C** (LUNA `READ/WRITE/RS*`).
  - 2 = 10 ms tick (8254 at `0xB0–0xBC`).
  - 3 = robot servo channel over **slot DPRAM windows** `0x700000+(slot−1)·0x10000`, slots 1–5.
  - 4 = RTC (ports `0x60–0x9C`).
  - 5 = 8 KB EEPROM at `0x600000`.
  - The PC card window is at `0x200000` (port `0x4C` selects attribute memory).
- **Interrupt hardware:** 8259A master at `0xA0/0xA4`, slave at `0xA8/0xAC` (vectors
  `0x20`/`0x28`). There is **no 8237 DMA**, and the "I/O board ports `0xC000…`" were a misread
  of the byte-port table at `0x4FD`. Port `0x20` is a status/halt-code output. Full IRQ map in
  the architecture report §4.3.
- **Reset entry:** `0x0`. It writes `0` to port `0x20`, zeroes BSS `0x461C..0x75F7`, runs the
  RAM-init stream (`0x5308`), PIC/PIT init (`0x5580`) and board init (`0x5104`), and jumps into
  pSOS+ (`0x558`). The root task `0x6CAC` starts `INIT` `0x6D3C`.
- **Robot:** SCARA, 4 axes XYZR. The robot language is **LUNA**, which compiles to
  *LUNA Object code* (`.OBJ`, produced on the host by `LUNNA.EXE`).
- Message tables are **bilingual English + Japanese (Shift-JIS)**, so IDA shows
  fragmented strings.
- **Errors:** the controller reports them to the teach pendant as numeric codes `E nnn`
  (E000…E401), plus a JP/EN message from the table at `0xD7E73…0xD99C7`.
  - The codes have gaps (hardware IRQ vectors are skipped).
  - The manual documents E000–E400. **E401 = "DSS off error"** (SMART-only Drive Safety
    Switch); see `doc/SRX-611_error_401_DSS_report.md`.

## 5. Key addresses (annotated)

| Addr | Name | Role |
|---|---|---|
| `0x0` | `reset_entry` | boot |
| `0x388` | `dma8237_init` (**misnamed**) | `usart_init`: reset + mode `0xCE` (8N2) on the three 8251A USARTs |
| `0x46C/0x4A4/0x4C9` | `io_read_status`/`io_read_data`/`io_write_data` | indexed I/O port access |
| `0x8BD4` | `sys_config_validate` | config validation (drives field validators) |
| `0x1535C` | `robot_task_main` | main application task (largest function) |
| `0x12D84` | `tp_menu_dispatch` | teach-pendant menu dispatch |
| `0x4F020`/`0x4DFB8` | `plc_scan`/`plc_program_exec` | PLC engine |
| `0x65C44` | `motion_param_process` | motion parameters |
| `0x6F7DC` | `point_var_dispatch` | point/variable name lookup |
| `0xBB5EC` | `db_access` (**misnamed**) | **Teach-pendant request** (`tp_request`) on serial ch1 `0x10001`: `1B LEN CMD …` frames, no checksum, TP status → `20000+s`. The `db_*` wrappers `0xBA35C`–`0xBB4F4` are the **TP command builders** (`0xBA35C` = `SRX6`/`TP4` handshake, `0xBAEDC` = cmd `60` display text). Command table: architecture report §8.1 |
| `0xCA6FC` | `pccard_file_op` | PC-card (FAT12) file ops |
| `0xC5CC4` | `token_dispatch` | LUNA object-code token dispatch (branches on token `≥80h` / `≤21h`; token codes in `doc/LUNA_token_map.md`) |
| `0xD99D2` | PLC mnemonic table | `END MC MCE JP( JPE( T C MOV( CMP( DEC( INC( CRST( FILL( ADD( SUB( BGET( BSET( CGET( CSET(`: same content and order as `DPLC.EXE`. Records have a 7-byte header (`02 xx F1 00 00 len 00`) + name. **Not** a LUNA table (older notes said so, and listed a bogus `N`) |
| `0xD80C9`..`0xD8720` | LUNA error strings | interpreter error set |
| `0x50D00` | `host_cmd_server_task` (Ghidra) | PC host-protocol server on OS channel `0x10002`: receive frame, `cmd ≥ 0xAC` → status 3, else `host_cmd_table[cmd]` |
| `0x51180` / `0x51088` | `host_rx_frame` / `_retry` | frame reader: timeout 5, bad ESC 2, LEN≤4 → 4, bad sum 1 (= E4000+s on the PC) |
| `0x51828` | `host_cmd_table` | 172 absolute handler pointers (`host_cmd_00`…`host_cmd_AB`; default `0x51360`) |

### 5.1 Error-reporting system (see `doc/SRX-611_error_401_DSS_report.md`)

| Addr | Name | Role |
|---|---|---|
| `0xD7E73` / `0xD7E81` | error message table start | JP/EN `"Divide error"` = **E000**; table is JP+EN NUL-terminated pairs up to `0xD99C7` |
| `0xD99A3` | `"SPD over speed error"` | **E400** (last code in the manual) |
| `0xD99C7` | `"DSS off error"` | **E401** = Drive Safety Switch off (SMART-only, absent from the manual) |
| `0x3BD28` | `app_3BD28` | servo-ON request handler — **raises error 401** (`sys_req_27h(ch,0,0x191)` at `0x3BE1B`) |
| `0x10334` | `plc_10334` | returns `(loc_6228 & 0x10) != 0` (servo-ON enable condition) |
| `0x10C5C` | `app_10C5C` | read system-input bit *n* (`app_3BD28` passes `n=7` → bit `0x40` of `loc_62B8` = DSS input) |
| `0x62B8` | `loc_62B8` | system-input image (word array, refreshed at `0x109F1`/`0x10B00` from `os_6238` pointers) |
| `0xBE214` | `sys_req_27h` | builds error request `(channel, subcode, code)` |
| `0xCE11D` | `os_syscall_90h_27h` | pSOS+ **`q_send`** (`EAX=0x27`); `sys_req_27h` uses it to post to the ERRT task's queue |

## 6. Annotation conventions used in the DB

- **Semantic names** where the function has been identified (e.g. `robot_task_main`,
  `db_var_get`, `plc_scan`).
- **Auto names:** `<category>_<HEXADDR>` (e.g. `util_653FC`, `motion_BB13C`).
  Categories: `os, util, db, sys, plc, disp, field, motion, point, app, config,
  param, task, cmd, math, io, tp, isr, record, format, str, ...`
- **Every function** has a comment of the form
  `[SRX-611] pop_rank=N/1298, sites=X, callers=Y, callees=Z, size=0xS`. Important
  functions get a semantic comment prepended.
- All 1298 functions are named and commented. `reset_entry` @`0x0` is a label, not a
  function.

## 7. IDA / tooling

- **IDA runs on the original Windows workstation only.** It is IDA Professional 9.0 at
  `C:\Program Files\IDA Professional 9.0`, with Hex-Rays.
  - A Linux checkout (like the current one) has no IDA and no `pypdf`. Here you can
    edit docs, read the `c_decomp*` sources, and do raw-byte analysis with plain Python
    (`python3`). For disassembly, create a venv in the session scratchpad and
    `pip install capstone`. Remember that the main CPU image is **32-bit** code
    (`CS_MODE_32`) while the SRXWIN DOS tools are 16-bit (`CS_MODE_16`, Borland large
    model: one code segment per source module, far calls `9A off seg`).
  - For work that needs the DB, prepare an IDAPython script and ask the user to run it.
### 7.1 Choosing tools

- Prefer the light workflow: a **capstone linear sweep** plus Python scripts (see the
  architecture report §13). Use Ghidra only for single functions (`DecompileByName.java`),
  one JVM at a time, and ask before any full analysis or decompile-all run.
- A killed Ghidra run leaves a stale `~/ghidra_projects/SRX611.lock`. Remove it only when no
  `analyzeHeadless` process is running.
- Keep scratch output (listings, dumps) in the session scratchpad, not in the repo.
- The saved Ghidra project currently holds only **seeded 3-byte function bodies** (the earlier
  full analysis was not saved). Single-function decompiling works, but listing/xref exports
  are incomplete. Rebuilding it (`import_rom1c.sh`) is a heavy job.

### 7.2 Ghidra, IDA rebase and IDA batch runs

- **Ghidra (on the Linux checkout, since 2026-09-26):** Ghidra 12.1.4 at
  `~/opt/ghidra_12.1.4_PUBLIC` with Temurin JDK 21 at `~/opt/jdk-21*`. These are user-level
  tarballs and not part of the repo.
  - The project is `~/ghidra_projects/SRX611`, program `ROM1-C.bin`: x86:LE:32, **based at
    `0xFFE00000`**. 2,241 functions are seeded (IDA has 1,298), and the absolute jump tables
    resolve. It is not versioned; recreate it with `tools/ghidra/import_rom1c.sh` and re-apply
    labels with `LabelSrxProtocol.java`.
  - Headless use:
    ```
    export JAVA_HOME=$(ls -d ~/opt/jdk-21*)
    ~/opt/ghidra_12.1.4_PUBLIC/support/analyzeHeadless ~/ghidra_projects SRX611 -process ROM1-C.bin \
      -noanalysis -readOnly -scriptPath tools/ghidra -postScript DecompileByName.java host_cmd_06 0x51180
    ```
  - Ghidra addresses are runtime addresses (`0xFFE50D00`). Docs keep **file offsets**
    (`0x50D00`), and IDA names are not imported into Ghidra.
- **IDA rebase:** `tools/ida/rebase_ffe00000.py` rebases the IDA DB to `0xFFE00000` and reports
  the before/after count of "invalid jump table" sites. The user asked for the rebase
  (2026-09-26). Run it on a copy first.
- **Batch run** (saves the DB on exit):
  ```
  & "C:\Program Files\IDA Professional 9.0\idat.exe" -A -L"<log.txt>" -S"<script.py>" "<workstation root>\FW\SRX6-CPU\2\ROM1-C.bin.i64"
  ```
  Scratch scripts and logs go in `C:\Users\radiolok\AppData\Local\Temp\kilo\`.
- **IDA 9 API gotchas** (already hit):
  - `ida_ida.get_inf_structure()` and `ida_ida.inf` do **not** exist. Use
    `ida_ida.inf_get_procname()`, `ida_ida.inf_get_min_ea()` and
    `ida_ida.inf_get_max_ea()` instead.
  - `ida_nalt.get_file_type_name()` does not exist.
  - Use `ida_funcs.set_func_cmt(ea, cmt, 0)` and
    `idc.set_name(ea, name, idc.SN_NOWARN)`.
- **Decompile:** `import ida_hexrays; ida_hexrays.init_hexrays_plugin(); str(ida_hexrays.decompile(ea))`.
- Backups of the DB from before annotation are in the workstation temp dir:
  `ROM1-C.bin.i64.bak` and `ROM1-C.bin.i64.annotated91.bak`.
- The `.i64` files are committed to git as binaries. If you modify a DB, commit it
  together with the doc and `history.md` updates that describe the change.

## 8. Important gotchas / lessons (read before analyzing)

1. **String xrefs do not resolve, because strings are used from RAM.** At boot `0x5308`
   copies the record stream at ROM `0xCE695–0xD9D94` (all strings, their pointer tables and
   initialised variables) into RAM `0x0–0xF221`, and the code references the **RAM
   addresses**. Use `tools/cpu/rom1c_raminit.py --find "text"` to get a string's RAM address,
   and `--ptr ADDR` to find pointer tables, then grep the code for that RAM address.
2. **IDA treats the switch jump tables as invalid** (`; switch with an invalid jump
   table`). The entries are addresses relative to the runtime base `0xFFE00000`, not
   file offsets, and many are relative. As a result, Hex-Rays fails on some functions.
   - Affected examples: `token_dispatch` (`0xC5CC4`), `record_get_field` (`0x1278C`),
     `record_get_field2` (`0x1265C`), `fn_C7C14`, `fn_C805C`, `point_var_dispatch` and
     `util_C667C`.
   - For these, read the assembly and reconstruct the C by hand. For the LUNA token
     decode, the LUNNA symbol table (`doc/LUNA_token_map.md`) is the host-side key.
   - Verified example: `token_dispatch` jumps via `jmp [eax*4+0FFEC5E64h]`, and the
     table at file `0xC5E64` holds absolute entries (`0xFFEC5D24`, …). **Rebasing the
     IDA segment to `0xFFE00000`** should let IDA resolve these tables. The user asked for it (2026-09-26), and the script
     is `tools/ida/rebase_ffe00000.py`; it is untested, so run it on a copy. Ghidra already
     loads the image at `0xFFE00000` (§7). The rebase will **not** fix string xrefs
     (checked: strings are not referenced by absolute pointers).
3. **Scanning operands via `idautils.Functions()` can miss references.** A more
   reliable way to find references to `loc_XXXX`/`byte_XXXX` labels is a **text scan**
   of `idc.generate_disasm_line(ea, 0)` with a regex such as
   `\b(?:loc|byte|word|dword|off|qword)_[0-9A-Fa-f]{4,6}\b`.
4. **Watch hex-digit counts.** A label like `loc_F12C` is the **low** address
   `0x0F12C`, *not* `0xF12C` inside the `0xF0000` region. `0xF1200` ≠ `0xF12C`.
5. **The 0xF000–0xF200 region is code** (small variable get/set functions using x87),
   not the `0xF0000` block.
6. Batch runs **repacked** the `.i64`. The original `.id0/.id1/.nam/.til` are gone
   because their data is now inside the `.i64`, so don't be surprised by their absence.
7. `Luna` is the robot programming language. It is **not** related to strings in the OS
   banner.
8. `ROM1-C.bin` loads at address `0x0` in IDA, as a single CODE segment (`seg000`).
9. **The error-message table has no pointer table in ROM, but it has one in RAM.**
   - The ROM copies (`0xD7E73…0xD99C7`) are never referenced. At runtime the RAM table
     at **`0x26F4`** holds `{JP*, EN*}` per code (`code*8 + lang*4`); E401 → RAM
     `0x337C/0x3380` → `"DSS off error"` @RAM `0xF11C`. It is read at `0x6DE0C` and
     `0x824E9`.
   - To find where a code is raised, search the binary for its 16-bit constant. For
     example, `0x191` (= 401) occurs only at `0x3BE1B`.
10. **The TP firmware (32 KB, `IC6_M27C256B@DIP28.BIN`) contains no error strings.** All
    `E nnn` text is produced by the CPU board (`ROM1-C.bin`).
11. **Chip images are not always a simple concatenation.**
    - The servo board's two 128 KB P28F010 flashes are **byte-interleaved** (U41 even +
      U42 odd) to make `ROM_SERVO.bin`.
    - The CPU board's U24/U25 dumps do **not** combine into `ROM1-C.bin` by plain
      concatenation or interleave (verified).
    - When an assembled `*.bin` / `*.i64` image exists, treat it as authoritative.
12. **Paths in older docs use Windows style** (`FW\SRX6-CPU\2\…`). They map 1:1 to the
    repo-relative `FW/SRX6-CPU/2/…`.

## 9. Common tasks & snippets

**Dump a function's disassembly:**
```python
f = ida_funcs.get_func(ea); p = f.start_ea
while p < f.end_ea:
    print("0x%X: %s" % (p, idc.generate_disasm_line(p, 0)))
    nx = idc.next_head(p, f.end_ea); p = nx if (nx != p and nx != idaapi.BADADDR) else p + 1
```

**Dump the call graph for a function:** get callers via `XrefsTo` and find callees by
scanning for `call`.

**Walk the whole image by instruction:**
```python
ea = 0
while ea < 0x100000:
    ...
    nx = idc.next_head(ea, 0x100000)
    ea = nx if (nx != ea and nx != idaapi.BADADDR) else ea + 1
```

**Search the raw image without IDA** (works on the Linux checkout):
```python
data = open("FW/SRX6-CPU/2/ROM1-C.bin", "rb").read()
import struct, re
hits = [m.start() for m in re.finditer(re.escape(struct.pack("<H", 0x191)), data)]
```

**Popularity metric used:** the number of code call-sites that reference a function
entry (`XrefsTo(ea)` with `iscode`), tie-broken by distinct callers, then by size.

**Extract the manual's error list (PDF):** `pypdf` is installed on the workstation. On
Linux you need `pip install pypdf` first.
```python
import pypdf, re
t = "\n".join(p.extract_text() or "" for p in pypdf.PdfReader("books/Sony+SRX+Scara+robot.pdf").pages)
# the guide prints codes spaced out: "E 0 0 0 : Divide error"
for m in re.finditer(r"E\s*(\d)\s*(\d)\s*(\d)\s*:\s*([^\r\n]+)", t):
    code = int(m.group(1)+m.group(2)+m.group(3)); desc = m.group(4).strip()
```
The Error Code Guide is on the last ~25 pages (section "Error Code Guide → Error Code
Lists"), and the codes are `E000…E400` only. E401 appears in neither the manual nor
`SRXMONIE.HLP` (firmware only). The E4001–E4408 codes (protocol status / host errors) are in
`doc/SRXMONIE_help.md` and `doc/SRXWIN_protocol.md` §2.1.

## 10. Subsystem summary (CPU board)

- **Boot + pSOS+/386 kernel + BSP** (`0x0`–`0x6CAB`): ISR stubs, USART init, kernel `0x518`–`~0x3DCB`, drivers (serial, tick, slot DPRAM, RTC, EEPROM). Then root/INIT/servo bring-up (`0x6CAC`–`0x7E53`). Syscall wrappers are at `0xCDE13`–`0xCE556`.
- **Config validation** (`0x8BD4` + field validators `0xA8C4`–`0xDB94`).
- **TP link** (`0xBA35C`–`0xBB733`): the old "variable DB" `db_*` functions are TP command builders (see §5).
- **PLC engine** (`0x4xxxx`).
- **Motion / point** (`0x6xxxx`–`0x8xxxx`).
- **Teach-pendant UI + string tables** (`0xC0000`–`0xD8000`):
  - Menus are at `0xD04xx`–`0xD1587`.
  - Diagnostic labels start at `0xD2F25`.
  - Error messages are at `0xD7E73`–`0xD99C7` (ROM copy; used from RAM, see §8.1/§8.9).
- **Error reporting** (`E000`–`E401`):
  - Path: `sys_req_27h` (`0xBE214`) → `q_send` (`0xCE11D`, `int 90h` fn `0x27`) → ERRT
    task `0xBDDCC` → text from the RAM table `0x26F4` → TP.
  - Error 401 is raised by `app_3BD28` (`0x3BD28`) from the DSS input bit (`0x62B8`
    bit 6).
- **LUNA language** (`0xC5xxx`–`0xC8xxx` decode/format cluster; token codes from
  `LUNNA.EXE`, see `doc/LUNA_token_map.md`). `0xD99D2` is the **PLC** mnemonic table.
- **Teach pendant** (a separate MCU, not on the CPU board): see §2.2 and
  `doc/TP_firmware_structure.md`.
- **Host link:** the RS-232C "programming device" channel (OS serial channel `0x10002`)
  talks to the SRXWIN tools; see `doc/SRXWIN_protocol.md` (ESC frames, 9600 8N2, status =
  E4000+s).
  - Firmware side: `host_cmd_server_task` `0x50D00` → `host_cmd_table` `0x51828`
    (172 handlers, §9 of that doc).
  - The second ESC-framed link on channel `0x10001` (`0xBB5EC`) is the **teach pendant**
    (handshake `SRX6`→`TP4`, no checksum). Channel `0x10003` is the user RS-232C port.
- **Tasks** (pSOS+ names): `INIT` `0x6D3C`, `SYST` `0x7E54`, `TPCT` `0x62A54`, `PLCT` `0xBE63C`,
  `PCCT` `0x50D00`, `SVTn` `0x37840` (servo cycle, paced by the slot IRQ; it also runs the
  PLC scan), `TJTn` `0x3E0A0`, `MNTn` `0x47CC0`, `HMTn` `0x45180`, `LTnn` `0x14D6C` (LUNA →
  `robot_task_main` `0x1535C` → `luna_exec_stmt` `0x23790` → 256-entry token table `0x237D8`),
  `ERRT` `0xBDDCC`.
- **SMART safety option:** DSS (Drive Safety Switch, `DSS0`/`DSS1` on safety-connector
  pins 12/13) plus the SPD PANEL BOARD over-speed detector. These raise E400
  (`SPD over speed`) and E401 (`DSS off`).

## 11. Notes on deliverables

- `c_decomp/*.c` and `c_decomp_luna/*.c` embed, for each function, the **original
  assembly as comments** (address: bytes mnemonic), followed by the C equivalent.
- The Hex-Rays output uses the annotated function names, and addresses are file
  offsets.
- If you re-run the generation scripts, keep functions grouped by the first token of
  their name (`prefix`).
- New reports go in `doc/`. Link each one from `README.md` §4 and §3.1 above, and log
  it in `history.md`.

## 12. Open work (as of 2026-09-26)

- CPU firmware:
  - Finish the decompilation (hand-reconstruct the switch-heavy functions, §8.2).
    Rebase the IDA DB to `0xFFE00000` first (`tools/ida/rebase_ffe00000.py`, run by the
    user on the workstation), or work in Ghidra, which is already rebased.
  - ~~Locate the host-protocol handler~~ (done: `0x50D00`/`0x51828`). Next: name the 152
    `host_cmd_XX` handlers in Ghidra, especially the ~40 not used by SRXWIN.
    ~~Identify the peer on `0x10001`~~ (done: teach pendant).
  - Apply the v2 names (architecture report §11) to the IDA DB (IDAPython script, run on the
    workstation).
  - Confirm the servo DPRAM per-axis field meanings against the V810 servo firmware, and the
    slot population of the real unit (architecture report §12).
  - Use the LUNA token table (`doc/LUNA_token_map.md`) to label `token_dispatch` cases.
- Boot EPROM: write up the analysis (only IDA DBs exist).
- Servo board: document `ROM_SERVO.bin` (V810, code at `0x00100000`; monitor console, amplifier diagnostics, DPRAM side of the slot protocol).
- Servo-I/O board: load `U7`/`U18` into IDA and identify the CPU.
- SRXWIN-NG (`srxwin-ng/`; stage 0 + stage-1 gate done 2026-09-27 against the fake):
  - Stage 3: decode `.DAT/.COD/.OBJ` from the golden corpus, then build the
    DISPON/DPLC/ANNUL equivalents. Grow the corpus to one file per keyword.
  - Stage 5: extend `srx_fake` with the SRXMONIE monitoring commands (firmware
    `host_cmd_table` `0x51828`), then run SRXMONIE in Win 3.11/86Box against it.
  - Hardware: record real sessions and confirm the [H] items in
    `srxwin-ng/docs/spec/PROTOCOL.md`. Obey spec §8.
- SRXWIN (done 2026-09-26: help extraction, LUNA symbol table, DOS-tool protocol):
  - Name the ~110 SRXMONIE monitoring commands (NE relocation → caller → menu/window).
  - Decode the `.OBJ` statement encoding (ANNUL statement decoder, or compile test
    programs with the original LUNNA under DOSBox-X and diff).
  - Confirm the protocol on hardware with a serial sniffer (SRXWIN-NG stage 1; obey the
    spec's §8 safety rules).
- Cross-map the CPU↔TP↔servo↔servo-I/O communication protocols (CPU side of TP, PC, user RS-232C and servo DPRAM done in the architecture report v2; TP handlers marked [H] and the servo board side remain).
