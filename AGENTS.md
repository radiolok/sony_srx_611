# AGENTS.md — Sony SRX-611 reverse engineering

Context file for AI coding agents working anywhere in this project.
Project root: `D:\radiolok@oc.urlnn.ru\Datasheets\SONY SRX`
Main analysis workdir (CPU-board firmware): `D:\radiolok@oc.urlnn.ru\Datasheets\SONY SRX\FW\SRX6-CPU\2`

Notice: For any investigations generate Markdown artifacts or modify existed.

Each session must add new bullet into history.md file which describe in 1-2 sentence what it did
Each new user data must update this description. e.g.

- Made SRXWIN analysis, save artifacts. etc.

Notice: If you are not sure is some ideas - ask a question instead of taking the desicion by your own

## 1. What this project is

Reverse engineering (static, IDA-based) of the **Sony SRX-611 SCARA robot controller**
and its surrounding boards. The primary focus is the **CPU-board firmware**: its OS, the
robot application, and the **LUNA** robot-programming language, plus annotation of the
IDA database. The other boards' firmware (servo, servo-I/O, teach pendant) and the
PC-side tooling are summarised at a high level in §2 so an agent can place any binary it
is asked about before diving into the detailed CPU-board notes (§3–§11).

## 2. Firmware / binary inventory (all boards)

| Board / image | Location (from project root) | Device(s) | CPU / bus | What it is | Analysis state |
|---|---|---|---|---|---|
| CPU main firmware `ROM1-C.bin` | `FW\SRX6-CPU\2\` | 2× MT28F400B5 flash (U24+U25), 512 KB each | Intel 80486, 16-bit real mode w/ 32-bit regs | 1 MB controller OS + robot application (the main target) | **Fully analysed** — `ROM1-C.bin.i64`, reports in §3 |
| CPU boot EPROM | `FW\SRX6-CPU\2\U23_M27C256B@DIP28.BIN`, `FW\SRX6-CPU\1\U26_M27C256B@DIP28.BIN`, `FW\SRX6-CPU\M27C256B@DIP28.BIN` | M27C256B, 32 KB | Intel 80486 (real mode) | Boot/monitor EPROM, separate from the main image. All three files are the **same image** (MD5 `AD0652D1…`) | IDA DBs exist (proc `80486r`): `FW\SRX6-CPU\1\U26_….i64` and unpacked `.id0/.id1/.nam/.til` next to `FW\SRX6-CPU\M27C256B@DIP28.BIN` |
| Teach pendant (TP) EPROM | `FW\TP\IC6_M27C256B@DIP28.BIN` | M27C256B, 32 KB | Hitachi **HD64180/Z180** | Thin terminal: keypad, 20-char display, serial command interpreter | Analysed — DB `IC6_….i64`, report `doc\TP_firmware_structure.md` (§2.2) |
| Servo board `ROM_SERVO.bin` | `FW\SRX6-SERVO\` | 2× P28F010 flash (U41+U42), 128 KB each | 16-bit bus (byte-interleaved) | Servo amplifier/monitor firmware. `ROM_SERVO.bin` (256 KB) = U41 even bytes + U42 odd bytes | IDA DB `ROM_SERVO.bin.i64` exists; detailed analysis not written up |
| Servo-board PLD | `FW\SRX6-SERVO\2\U43.GAL16V8B.JED` | GAL16V8B | — | Glue logic / address decode JEDEC | Raw dump only |
| Servo-I/O board EPROMs | `FW\SERVO_IO\1\U7_M27C512@DIP28.BIN`, `FW\SERVO_IO\1\U18_M27C512@DIP28.BIN` | 2× M27C512, 64 KB each | 32-bit RISC (likely NEC µPD70732 / V810) | Servo-I/O controller pair (128 KB total). **No ASCII strings** in the raw dumps | Not analysed |
| PC-side tools | `SRXWIN\SRXWIN\*.EXE` (+ `SRXWIN.zip`) | — (x86 DOS/Windows) | — | Sony host software: `LUNNA.EXE`/`LUNNAPR.EXE` (LUNA), `SRXMONIE.EXE`+`.HLP` (monitor), `PLC.EXE`, `POINT.EXE`, `MONIT.EXE`, `RECALL.EXE`, `SEND.EXE`, `DPLC.EXE`, `DISPON.EXE`, `ANNUL.EXE`, `FDEL.EXE`, `FILES.EXE`, `HIST.EXE`, `INSTALLE.EXE`, `INI_RS.EXE`/`INI_RS98.EXE` | Not analysed |

### 2.1 CPU board (SRX6-CPU) — main controller

- **Main firmware** = the 1 MB image `ROM1-C.bin` assembled from the two 512 KB
  `MT28F400B5` flash devices **U24** and **U25** (TSOP48). This is the image the whole
  §3–§11 analysis refers to.
  - Note: a raw byte concatenation or byte-interleave of the U24/U25 dumps does **not**
    reproduce `ROM1-C.bin` (verified), so treat `ROM1-C.bin` as the authoritative image.
- **Boot EPROM** = 32 KB `M27C256B` (socket U23 / U26), a separate x86 real-mode image.
  All three on-disk copies are identical (see table).
- CPU is an Intel/IBM 80486 (DX2-66 / DX4 datasheets in `FW\`).

### 2.2 Teach pendant (TP)

- 32 KB `M27C256B` (socket IC6), Hitachi **HD64180** (Z180/Z80-compatible), IM2, ASCI.
- Only ~`0x205A` of ROM used; 121 functions; **no robot logic and no error text** — the
  CPU board formats all text. Handshake: CPU sends `"SRX6"`, TP replies `"TP4"`.
- Full report: `doc\TP_firmware_structure.md`.

### 2.3 Servo board (SRX6-SERVO)

- Two P28F010 flash devices (`1\U41_P28F010@DIP32.HEX` + `1\U42_P28F010@DIP32.BIN`,
  128 KB each) form a 16-bit bus: **U41 = even/low bytes, U42 = odd/high bytes**, giving
  `ROM_SERVO.bin` (256 KB).
- `2\U43.GAL16V8B.JED` is a GAL16V8B PLD.
- Firmware strings identify a **"Servo Board Monitor / Copyright(C) 1995 Sony Corp."**
  serial console (`VER`, `CONNECT`, `ABSCOPY`, `HELP`) with amplifier diagnostics
  (`AMP ERROR(axis 1/2): watch dog|hardware|software|initialize`) and a full servo/amp
  error list. It references **SRX-610** and **SRX-630(FEB)**.
- CPU / bus details not yet confirmed; raw ROM has no legible ASCII CPU banner.

### 2.4 Servo-I/O board (SERVO_IO)

- Two 64 KB `M27C512` EPROMs (`U7`, `U18`) = 128 KB program space. Raw dumps contain
  **no printable ASCII strings** (code/numeric data only), so no banner has been recovered.
- A **NEC µPD70732 (V810, 32-bit RISC)** datasheet is present at project root and is the
  likely CPU for this board (unconfirmed). Not yet loaded into IDA.

### 2.5 PC-side tools (SRXWIN)

- `SRXWIN\SRXWIN\*.EXE` — Sony host software for Windows/DOS (`SRXWIN.zip` archive):
  LUNA language tools (`LUNNA.EXE`, `LUNNAPR.EXE`), monitor (`SRXMONIE.EXE` + help),
  `PLC.EXE`, `POINT.EXE`, `MONIT.EXE`, `RECALL.EXE`, `SEND.EXE`, plus RS-232 setup
  (`INI_RS.EXE`/`INI_RS98.EXE`). Useful as the host-side view of controller protocols,
  file formats and the LUNA toolchain.

### 2.6 Support documents, design files and component datasheets (project root)

| Path | Meaning |
|---|---|
| `Sony+SRX+Scara+robot.pdf` | SRX operation manual (268 pp). Contains the **Error Code Guide** E000–E400 (E401 absent). |
| `37996036.pdf` / `37996036_EN.pdf` | SRX611 user training manual (Tampere 2007 thesis; EN copy is machine-translated). |
| `SPD Panel Board.odg` / `.pptx`, `SPD_panel_relays.dch` | SPD (speed-detector) panel-board presentation, diagram and relay design. |
| `Intel-80486DX2-66-datasheet.pdf`, `FW\IBM_486DX4.pdf` | CPU-board processor datasheets. |
| `UPD70732GD(A)-25-LBB.pdf` | NEC µPD70732 = V810 32-bit microprocessor (servo-family boards). |
| `FW\M27C256B.pdf`, `FW\MB8432.PDF` (scanned), `FW\SG51PH-50MHZ.pdf` (oscillator), `FW\m7000-1299427.pdf` (Altera MAX 7000 PLD) | Component datasheets. |
| `SRXWIN.zip` | Archive of the PC-side tools (§2.5). |
| `join_fw.py` | Non-working helper (malformed) intended to join firmware halves (`-l`/`-h`). |

Duplicate/backup directories: `FW\SRX6-CPU\2 — копия\` is a copy of `FW\SRX6-CPU\2\`.

## 3. Files in the CPU-board workdir (`FW\SRX6-CPU\2`)

The paths below are relative to `FW\SRX6-CPU\2`.

| File | Meaning |
|---|---|
| `ROM1-C.bin` | 1 MB firmware image under analysis (linear image base `0x0`..`0x100000`) |
| `ROM1-C.bin.i64` | IDA Pro 9.0 database — **packed/self-contained** (originally unpacked with `.id0/.id1/.nam/.til`, now merged). Contains all annotations. |
| `U23_M27C256B@DIP28.BIN` | 32 KB boot EPROM (M27C256B) — separate from main firmware |
| `U24_MT28F400B5-T@TSOP48.BIN` | 512 KB flash |
| `U25_MT28F400B5-T@TSOP48.BIN` | 512 KB flash (U24+U25 = the 1 MB main firmware) |
| `c_decomp/` | C equivalents (Hex-Rays) of the **top-50** functions, grouped by name prefix |
| `c_decomp_luna/` | C equivalents of the **LUNA** subsystem (43 functions) |

The analysis reports for this firmware live in **`doc\`** at the project root (see
`README.md` §4): `SRX-611_firmware_architecture.md`, `SRX-611_error_401_DSS_report.md`,
`TP_firmware_structure.md`, `function_popularity.md`, `LUNA_analysis.md`.

Related files elsewhere in the project:

| Path (from project root) | Meaning |
|---|---|
| `Sony+SRX+Scara+robot.pdf` | SRX operation manual (268 pp, ~1.8 MB). Contains the **Error Code Guide** (`E nnn : message`, codes E000…E400) — use `pypdf` to extract text. Error 401 is **not** in it (SMART-only / later FW). |
| `FW\TP\IC6_M27C256B@DIP28.BIN` | 32 KB teach-pendant firmware (**HD64180/Z180**, ROM `0x0-0x7FFF`, RAM `0x8000-0xFFFF`; only ~`0x205A` used). TP has **no** error strings — text is formatted by the CPU board. See `doc\TP_firmware_structure.md`. |
| `FW\TP\IC6_M27C256B@DIP28.BIN.i64` | IDA DB for the TP firmware (proc `64180`). |

## 4. Target platform (CPU board, facts)

- **CPU:** Intel 80486 (386-class), 16-bit real mode **with 32-bit register use**
  (big-real/unreal mode). IDA processor module: `80486r`. FPU (x87) present.
- **OS:** Sony `OS+/386 V2.0` (banner @`0x5BA`, copyright 1993 @`0x60C`).
- **Runtime base:** code/data is referenced at **`0xFFE00000 + file_offset`**.
  File offset = runtime address − `0xFFE00000`. (e.g. `0xFFEBFF4C` → file `0xBFF4C`.)
- **Syscall ABI:** function code in `EAX`, then `int 90h` or `int 91h`.
  Wrappers live at `0xCDE14`–`0xCE58C`, named `os_syscall_90h_XXh` / `os_syscall_91h_XXh`.
- **Interrupt hardware:** 8259A PICs (`0x20/0xA0`, `0xA0/0xA8`); 8237A DMA (ports
  `0xC4/0xCC/0xD4`); I/O board ports `0xC000 / 0xC800 / 0xCC00 / 0xD000 / 0xD400`.
- **Reset entry:** `0x0` (EI0 master PIC, zero BSS `0x461C..0x75F7`, init calls).
- **Robot:** SCARA, 4 axes XYZR. Language = **LUNA** (compiles to *LUNA Object code*).
- Message tables are **bilingual English + Japanese (Shift-JIS)** → IDA shows fragmented strings.
- **Errors:** reported to the teach pendant as numeric codes `E nnn` (E000…E401) plus a
  JP/EN message from the table at `0xD7E73…0xD99C7`. Codes have gaps (skip hardware IRQ
  vectors). The manual documents E000–E400; **E401 = "DSS off error"** (SMART-only
  Drive Safety Switch), see `doc\SRX-611_error_401_DSS_report.md`.

## 5. Key addresses (annotated)

| Addr | Name | Role |
|---|---|---|
| `0x0` | `reset_entry` | boot |
| `0x388` | `dma8237_init` | DMA init |
| `0x46C/0x4A4/0x4C9` | `io_read_status`/`io_read_data`/`io_write_data` | indexed I/O port access |
| `0x8BD4` | `sys_config_validate` | config validation (drives field validators) |
| `0x1535C` | `robot_task_main` | main application task (largest function) |
| `0x12D84` | `tp_menu_dispatch` | teach-pendant menu dispatch |
| `0x4F020`/`0x4DFB8` | `plc_scan`/`plc_program_exec` | PLC engine |
| `0x65C44` | `motion_param_process` | motion parameters |
| `0x6F7DC` | `point_var_dispatch` | point/variable name lookup |
| `0xBB5EC` | `db_access` | variable/parameter DB accessor |
| `0xCA6FC` | `pccard_file_op` | PC-card (FAT12) file ops |
| `0xC5CC4` | `token_dispatch` | LUNA object-code token dispatch |
| `0xD99D2` | LUNA opcode/keyword table | `END,MC,MCE,JP(,JPE(,T,C,N,MOV(,CMP(,DEC(,INC(,ADD(,SUB(,CRST(,FILL(,BGET(,BSET(,CGET(,CSET(,=,PCCD` |
| `0xD80C9`..`0xD8720` | LUNA error strings | interpreter error set |

### 5.1 Error-reporting system (see `doc\SRX-611_error_401_DSS_report.md`)

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
| `0xCE11D` | `os_syscall_90h_27h` | `EAX=0x27`, `int 90h` → error/event task → teach pendant |

## 6. Annotation conventions used in the DB

- **Semantic names** where identified (e.g. `robot_task_main`, `db_var_get`, `plc_scan`).
- **Auto names:** `<category>_<HEXADDR>` (e.g. `util_653FC`, `motion_BB13C`).
  Categories: `os, util, db, sys, plc, disp, field, motion, point, app, config,
  param, task, cmd, math, io, tp, isr, record, format, str, ...`
- **Every function** has a comment: `[SRX-611] pop_rank=N/1298, sites=X, callers=Y, callees=Z, size=0xS`
  (semantic comment is prepended for important functions).
- All 1298 functions are named and commented. `reset_entry` @`0x0` is a label (not a function).

## 7. IDA / tooling

- IDA Professional 9.0 at `C:\Program Files\IDA Professional 9.0` (Hex-Rays present).
- **Batch run** (saves DB on exit):
  ```
  & "C:\Program Files\IDA Professional 9.0\idat.exe" -A -L"<log.txt>" -S"<script.py>" "D:\...\ROM1-C.bin.i64"
  ```
  Scratch/scripts/logs go in `C:\Users\radiolok\AppData\Local\Temp\kilo\`.
- **IDA 9 API gotchas** (already hit):
  - `ida_ida.get_inf_structure()` and `ida_ida.inf` do **not** exist → use
    `ida_ida.inf_get_procname()`, `ida_ida.inf_get_min_ea()`, `ida_ida.inf_get_max_ea()`.
  - `ida_nalt.get_file_type_name()` does not exist.
  - Use `ida_funcs.set_func_cmt(ea, cmt, 0)`, `idc.set_name(ea, name, idc.SN_NOWARN)`.
- **Decompile:** `import ida_hexrays; ida_hexrays.init_hexrays_plugin(); str(ida_hexrays.decompile(ea))`.
- Backups of the DB (pre-annotation) live in the temp dir:
  `ROM1-C.bin.i64.bak`, `ROM1-C.bin.i64.annotated91.bak`.

## 8. Important gotchas / lessons (read before analyzing)

1. **String xrefs do not resolve.** `idautils.XrefsTo` on a string address returns
   nothing; `ida_search.find_imm` finds nothing. Strings are referenced via computed
   pointers or relative offsets. Do not rely on string xrefs.
2. **Switch jump tables are "invalid" to IDA** (`; switch with an invalid jump table`)
   because entries are addresses relative to runtime base `0xFFE00000`, not file
   offsets, and many are relative. Consequently Hex-Rays fails on some functions.
   Affected examples: `token_dispatch` (`0xC5CC4`), `record_get_field` (`0x1278C`),
   `record_get_field2` (`0x1265C`), `fn_C7C14`, `fn_C805C`, `point_var_dispatch`,
   `util_C667C`. For these, read the assembly and reconstruct C by hand.
3. **Operand scanning via `idautils.Functions()` can miss references.** A more reliable
   detector for references to `loc_XXXX`/`byte_XXXX` labels is a **text scan** of
   `idc.generate_disasm_line(ea, 0)` with a regex like
   `\b(?:loc|byte|word|dword|off|qword)_[0-9A-Fa-f]{4,6}\b`.
4. **Watch hex-digit counts.** Labels like `loc_F12C` are the **low** address
   `0x0F12C`, *not* `0xF12C` inside the `0xF0000` region. `0xF1200` ≠ `0xF12C`.
5. **The 0xF000–0xF200 region is code** (small variable get/set functions using x87),
   not the `0xF0000` block.
6. The `.i64` was **repacked** by batch runs; the original `.id0/.id1/.nam/.til` are gone
   (data is inside the `.i64`). Do not be surprised by their absence.
7. `Luna` = robot programming language; **not** related to strings in the OS banner.
8. `ROM1-C.bin` load address in IDA is `0x0` (single CODE segment, `seg000`).
9. **The error-message table has no pointer/xref table.** Messages (`0xD7E73…0xD99C7`)
   are addressed by error code with gaps; `XrefsTo` on any message is empty and the
   table base is never an immediate. To find a code's origin, search the binary for the
   16-bit constant (e.g. `0x191`=401 occurs only at `0x3BE1B`).
10. **The TP firmware (32 KB, `IC6_M27C256B@DIP28.BIN`) contains no error strings**;
    all `E nnn` text is produced by the CPU board (`ROM1-C.bin`).
11. **Chip images are not always a simple concatenation.** The servo board's two
    128 KB P28F010 flashes are **byte-interleaved** (U41 even + U42 odd) to make
    `ROM_SERVO.bin`; the CPU board's U24/U25 dumps do **not** combine by plain
    concat/interleave into `ROM1-C.bin` (verified). Prefer the assembled `*.bin` /
    `*.i64` images as authoritative when they exist.

## 9. Common tasks & snippets

**Dump a function's disassembly:**
```python
f = ida_funcs.get_func(ea); p = f.start_ea
while p < f.end_ea:
    print("0x%X: %s" % (p, idc.generate_disasm_line(p, 0)))
    nx = idc.next_head(p, f.end_ea); p = nx if (nx != p and nx != idaapi.BADADDR) else p + 1
```

**Dump call graph for a function** (callers via `XrefsTo`, callees by scanning `call`).

**Walk the whole image by instruction:**
```python
ea = 0
while ea < 0x100000:
    ...
    nx = idc.next_head(ea, 0x100000)
    ea = nx if (nx != ea and nx != idaapi.BADADDR) else ea + 1
```

**Popularity metric used:** number of code call-sites referencing a function entry
(`XrefsTo(ea)` with `iscode`), tie-broken by distinct callers, then size.

**Extract the manual's error list (PDF):** `pypdf` 6.16.1 is installed (`python`).
```python
import pypdf, re
t = "\n".join(p.extract_text() or "" for p in pypdf.PdfReader(pdf).pages)
# the guide prints codes spaced out: "E 0 0 0 : Divide error"
for m in re.finditer(r"E\s*(\d)\s*(\d)\s*(\d)\s*:\s*([^\r\n]+)", t):
    code = int(m.group(1)+m.group(2)+m.group(3)); desc = m.group(4).strip()
```
The Error Code Guide is on the last ~25 pages (section "Error Code Guide → Error Code
Lists"); the codes are `E000…E400` only.

## 10. Subsystem summary (CPU board)

- **OS+/386 kernel** (`0x0`–`0x8BD4`): boot, PIC/DMA, ISRs, I/O, syscall wrappers.
- **Config validation** (`0x8BD4` + field validators `0xA8C4`–`0xDB94`).
- **Variable/parameter DB** (`0xBB5EC` `db_access` + typed accessors `db_*`).
- **PLC engine** (`0x4xxxx`).
- **Motion / point** (`0x6xxxx`–`0x8xxxx`).
- **Teach-pendant UI + string tables** (`0xC0000`–`0xD8000`; menus `0xD04xx`–`0xD1587`,
  diagnostic labels `0xD2F25`…, error messages `0xD7E73`–`0xD99C7`).
- **Error reporting** (`E000`–`E401`): `sys_req_27h` (`0xBE214`) → `os_syscall_90h_27h`
  (`0xCE11D`, `int 90h` fn `0x27`) → error/event task → TP. Error 401 generated by
  `app_3BD28` (`0x3BD28`) via DSS input bit (`0x62B8` bit 6).
- **LUNA language** (`0xC5xxx`–`0xC8xxx` decode/format cluster; opcode table `0xD99D2`).
- **Teach pendant (separate MCU, not the CPU board):** Hitachi **HD64180/Z180**, 32 KB
  ROM at `0x0-0x7FFF` (only ~`0x205A` used), IM2, ASCI serial. Thin terminal — super-loop
  command dispatcher (`sub_25C`), 20-char display, keypad. Handshake: CPU sends `"SRX6"`,
  TP replies `"TP4"` (else shows `MISMATCH`). **No error text in the TP.** See
  `doc\TP_firmware_structure.md`.
- **SMART safety option:** DSS (Drive Safety Switch, `DSS0`/`DSS1` safety-connector pins
  12/13) + SPD PANEL BOARD over-speed detector → errors E400 (`SPD over speed`) /
  E401 (`DSS off`).

## 11. Notes on deliverables

- `c_decomp/*.c` and `c_decomp_luna/*.c` embed, per function, the **original assembly as
  comments** (address: bytes mnemonic) followed by the C equivalent.
- Hex-Rays output refers to the annotated function names; addresses are file offsets.
- If you re-run generation scripts, keep functions grouped by the first token of their
  name (`prefix`).
