# SRXWIN host tools — structure report (Sony SRX)

**Scope:** `SRXWIN\SRXWIN\*.EXE` (+ `SRXWIN.zip`, `SRXMONIE.HLP`, `SRXMONI.ICO`)
**Era:** 1991‑02 … 1996‑11 · **Target controller:** Sony SRX‑5xx/6xx (SRX‑611)
**Relation to firmware:** host side of the LUNA/PLC toolchain and serial protocol analysed in
`SRX-611_firmware_architecture.md`, `LUNA_analysis.md`, `function_popularity.md`.

The `SRXWIN` folder is the complete **PC‑side toolchain** for the SRX controller. It is a
Borland‑C DOS suite of compilers, decompilers and serial utilities, wrapped by a 1996
MSVC/MFC Windows GUI ("SRX Platform", `SRXMONIE.EXE`) and installed by `INSTALLE.EXE`.
All files were verified byte‑identical to the contents of `SRXWIN.zip`.

---

## 1. Provenance and inventory

| File | Size | Date | Format / toolchain | Role |
|---|---:|---|---|---|
| `INSTALLE.EXE` | 116 400 | 1996‑10‑14 | NE (Win16), MSVC MFC | Installer "SRXINS", v1.0.001 |
| `SRXMONIE.EXE` | 431 216 | 1996‑11‑18 | NE (Win16), MSVC MFC | "SRX Platform" GUI shell v1.0.001 (JP locale, EN UI) |
| `SRXMONIE.HLP` | 392 976 | 1996‑11‑12 | Windows 3.x HLP | Full on‑line help / command reference |
| `SRXMONI.ICO` | 766 | 1996‑03‑27 | Windows icon | Program‑group icon |
| `LUNNA.EXE` | 141 232 | 1996‑07‑25 | DOS MZ, Borland C++ | **LUNA 5.0 compiler v1.05** (`.LUN` → `.OBJ`) |
| `ANNUL.EXE` | 90 512 | 1996‑08‑16 | DOS MZ, Borland C++ | **LUNA 5.0 decompiler v1.04** (`.OBJ` → `.LUN`) |
| `POINT.EXE` | 87 456 | 1996‑04‑24 | DOS MZ, Borland C++ | **POINT 5.0 compiler v1.04** (`.PON` → `.DAT`) |
| `DISPON.EXE` | 27 632 | 1996‑06‑24 | DOS MZ, Borland C++ | **Point data decompiler v1.2** (`.DAT` → `.PON`) |
| `PLC.EXE` | 69 440 | 1996‑04‑25 | DOS MZ, Borland C++ | **SRX PLC compiler v1.04** (`.PLC` → `.COD`) |
| `DPLC.EXE` | 52 592 | 1996‑04‑20 | DOS MZ, Borland C++ | **SRX PLC decompiler v1.03** (`.COD` → `.PLC`) |
| `LUNAPR.EXE` | 17 658 | 1991‑02‑15 | DOS MZ, Turbo C++ 1990 | LUNA printer/listing formatter (lex‑based) |
| `SEND.EXE` | 27 616 | 1996‑02‑28 | DOS MZ, Borland C++ | Send files PC → controller |
| `RECALL.EXE` | 32 848 | 1996‑02‑28 | DOS MZ, Borland C++ | Recall/decompile files controller → PC |
| `FILES.EXE` | 42 528 | 1996‑02‑28 | DOS MZ, Borland C++ | List controller program directory |
| `FDEL.EXE` | 26 944 | 1996‑02‑28 | DOS MZ, Borland C++ | Delete controller programs |
| `HIST.EXE` | 43 248 | 1996‑02‑28 | DOS MZ, Borland C++ | Dump/print controller error history |
| `MONIT.EXE` | 25 984 | 1996‑02‑28 | DOS MZ, Borland C++ | "Monitor program 5.0 (IBM‑PC)" serial monitor |
| `INI_RS.EXE` | 34 287 | 1996‑05‑21 | DOS MZ, Borland C++ | RS‑232C channel/port setup (IBM‑PC) |
| `INI_RS98.EXE` | 37 026 | 1996‑08‑08 | DOS MZ, Borland C++ | RS‑232C setup for NEC PC‑98 (BIOS COM) |

Two distinct lineages:

- **DOS 16‑bit console toolkit** (Borland C++ 1991): compilers/decompilers + communication
  utilities; all statically link one shared module (common usage/error strings appear verbatim
  in every binary).
- **Windows 16‑bit GUI shell** (MSVC/MFC, NE): `SRXMONIE.EXE` + `INSTALLE.EXE` + help. It does
  **not** reimplement the DOS tools — it drives them through `.PIF` files and exchanges
  text/data via `SRXWIN.INI`.

---

## 2. Architecture / how they fit together

```
      INSTALLE.EXE  (SRXINS, MFC installer)
            │  copies + creates program group "SRX"
            ▼
      SRXMONIE.EXE  ("SRX Platform" GUI, MFC MDI)
        │   SRXWIN.INI  : LUNA_DIR, FILE_DIR, MAIN_DIR, PORT, COMPILE_R, COMPILE_A
        │
        ├─ spawns .PIF ─► LUNNA.EXE  -E …   compile  .LUN → .OBJ
        ├─ spawns .PIF ─► POINT.EXE  -E -L [-C]   compile .PON → .DAT/.CDT/.MDT
        ├─ spawns .PIF ─► PLC.EXE    -E …   compile  .PLC → .COD
        ├─ spawns .PIF ─► ANNUL.EXE         decompile .OBJ → .LUN
        ├─ spawns .PIF ─► DISPON.EXE [-C]   decompile .DAT → .PON
        ├─ spawns .PIF ─► DPLC.EXE          decompile .COD → .PLC
        ├─ spawns .PIF ─► SEND.EXE / RECALL.EXE / FILES.EXE / HIST.EXE
        └─ spawns       ─► INI_RS.EXE / INI_RS98.EXE -P2   (port init)

      Standalone DOS CLI use:  SEND/RECALL/FILES/FDEL/HIST/MONIT + the compilers
```

Evidence: `INSTALLE.EXE` enumerates exactly `SRXMONIE.EXE`, `SRXMONIE.HLP`, `SRXMONI.ICO`,
`LUNNA.PIF`, `PLC.PIF`, `DPLC.PIF`, `ANNUL.PIF`, `POINT.PIF`, `DISPON.PIF`, `INI_RS.PIF`,
`INI_RS98.PIF`, and the group script `[CreateGroup("SRX")] … [AddItem(...)]`.
`SRXMONIE.EXE` embeds the exact command lines `LUNNA -E `, `POINT -E -L -C `, `POINT -E -L `,
`PLC -E `, `ANNUL `, `DISPON -C `, `DISPON `, `DPLC `, and the INI keys `LUNA_DIR=`,
`FILE_DIR=`, `MAIN_DIR=`, `PORT=`, `COMPILE_R=`, `COMPILE_A=`.

Default working files: `srxdata.cdt` (common data), `srxrelay.kee` (keep relays),
`srxpara.ctr` (robot parameters) — the GUI edits system data alongside user programs.

---

## 3. Tool‑by‑tool detail

### 3.1 Language toolchain

**`LUNNA.EXE` — LUNA compiler** (`LUNA 5.0 Version 1.05, Copyright SONY Corp. 1983,1996`)

- Source `.LUN`; output LUNA object `.OBJ`; library source `.LSF` → `.LIB`.
- Two‑pass compiler ("End of 1st pass", "End of 2nd pass", "Creation of Library Relocatable
  File", "Linking of Library Function …", "Object code %u bytes.", "Total object code %u bytes.").
- Diagnostics **2000–2089**, e.g. `2002 Open error %s`, `2005 too many INTEGERS`,
  `2008 too many FUNCTIONS`, `2030 Object size is beyond 255 bytes in step no. %s`,
  `2037 You missed RET statement at end of Subroutine`, `2057 Subroutine %s in LOOP`,
  `2065 Object file is over 64k byte`, `2089 You can not write Library after IF`.
- Contains the **LUNA reserved‑word/keyword table**: ACOS, AMVX/Y/Z/R, CIRCLE/CIRCLE2,
  DATI/DATR, FOSRST, GETERR, HOMING, MCDATI/R, MCLOAD/MCSAVE, MCOPEN/MCCLOSE, MVPULS,
  PALLET/PALLET4, PASSP, PFOS, PICTURE, RSSET/RSSPEED, SCALIB/GCALIB, TLDEF/TLSEL/TLRST,
  TYPESET, VCMD/VDAT/VGET/VEXE, INTRPT1‑5, …
- Options: `-D` show `.LUN`, `-W` stop on error, `-E` write `.ERR`, `-L` English, `-R` strip
  comments (smaller OBJ).

**`ANNUL.EXE` — LUNA decompiler** (`ANNUL 5.0 Version 1.04`)

- "LUNA" reversed; turns LUNA object code back into LUNA source. Strings: "Object file %s",
  "%s is not object file", `.obj`, `.lib`, `.bak`, `.lsf`, `.lun`, `copy %s %s`, plus a
  decompilation vocabulary (`DEF:`, `GO %s`, `CALL %s`, `A(%s)`, `B(%s)`, `(%d)`, `,ON)`/`,OF)`
  for I/O, `FOR … TO … STEP`).
- Carries an extensive opcode→mnemonic table (arithmetic, I/O, motion, RS‑232, task control) —
  host‑side counterpart of the firmware's LUNA token dispatcher (`token_dispatch` @`0xC5CC4`,
  table @`0xD99D2`).

**`POINT.EXE` — point/coordinate compiler** (`POINT 5.0 Version 1.04, Copyright SONY Corp. 1983,1996`)

- `.PON` → `.DAT` (point data); `.CPN` → `.CDT` (common data); `.MPN` → `.MDT` (memory‑card data).
- Geometry model: axes `XYZR` plus `TP(`, `OFFSET`, `RESET`, `LIMIT`, `LEFT`/`RIGHT`, `PSHIFT`,
  `PFLAG`, `ATAN`, `SQRT`, `DATI`/`DATR`/`MCDATI`/`MCDATR`.
- Diagnostics **2092–2133**, e.g. `2104 LN(minus) cannot be calculated`,
  `2115 Out of spec PFLAG data`, `2116 P%d(%d) cannot be defined`,
  `2119 OFFSET exist more than 255`, `2127 Endless loop exist`, `2133 Object file is over 64k byte`.
- Options: `-D`, `-W`, `-L`, `-C` (common `.CPN`), `-E` (.ERR), `-M` (memory‑card `.MPN`).

**`DISPON.EXE` — point decompiler** (`DISPON 5.0 Version 1.2`)

- `.DAT`→`.PON`, `.CDT`→`.CPN`, `.MDT`→`.MPN`; prints `Point data of`, `Discompile End`,
  `LIMIT`, `OFFSET`/`RESET`, `LEFT`/`RIGHT`, `P%d(%d)=`, `DATI`, `DATR`, `MCDATI`, `MCDATR`;
  version check "This file is another version."

**`PLC.EXE` — PLC compiler** (`SRX PLC Compiler Version 1.04, Copyright Sony Corp. 1996`)

- `.PLC` → `.COD`, error file `.ERR`, temp `.BUF`. Relay/channel model `R##C K##C T### C###
  I### L###`; special relays `ALLON/ALLOFF/FIRST/SCAN/CLK01/CLK02/CLK05/CLK1/CLK2/SMALL/LARGE/
  AUTO/ONLINE/OVERFLOW/ZERO/FULL`; logic ops; `DEF`, `MC/MCE`, `JP/JPE`, `CRST/FILL/BGET/BSET/
  CGET/CSET`; timers/counters require `:=`.
- Encoder error codes 3115/3116/3118/3120; limits `I001…I512`, `L001…L512`, relay bit 00–15,
  "COD File size exceeds limit of 32K bytes", JP number ≤ 99, label ≤ 10 chars, ≤ 255
  timers/counters.
- Options: `-L` English, `-R` strip comments; filename may include drive (`B:sample1`).

**`DPLC.EXE` — PLC decompiler** (`SRX PLC Discompiler Version 1.03, Copyright Sony Corp. 1996`)

- `.COD` → `.PLC`, `.BAK`, via DOS `COPY`/`DEL`; same 3115/3116/3118/3119/3120 error set;
  keyword table matches `PLC.EXE`.

**`LUNAPR.EXE` — LUNA printer/listing utility** (`LUNA-PRINTER UTILITY`,
`Copyright (C) 1991 Sony Corp.`, Turbo C++, lex source `lp.c v1.5 / lp.lex v1.1`, 90/04/12)

- Pretty‑prints LUNA source to printer or file with pagination, tab stops, column width,
  filename headers, code‑macro environment file (`-h -n -c -f -t -l -p -o -a`). Messages:
  "Output file specification required", "TAB STOP range must be 1 through 8",
  "PAGE SIZE must be 1 through 256", "Printer DEVICE not prepared", "Environment file not found".

### 3.2 Communication utilities (shared Borland runtime)

`SEND / RECALL / FILES / FDEL / HIST / MONIT / INI_RS / INI_RS98` embed the **same shared
module** (source paths `C:\L50\RS\SOURCE\misc.c`, `path.c`, `messg.c`, `rsfnc.c`; `INI_RS.C`
under `C:\L50\RS\SRXWIN\`). They share argument parsing, prompt text and the controller‑response
error list.

**Common option grammar**

- `-L` English display, `-P<1~3>` RS‑232C channel, `-T<0~180>` program type no., `-A` all
  programs, `-R<O,D,A,C,P>` kind, `-F<file|drive>`, `-D` controller‑data file.
- `<-RO>` = LUNA `.OBJ`, `<-RD>` = point `.DAT`, `<-RA>` = both, `<-RC>` = common data `.CDT`
  (PLC `.COD` in `INI_RS98` as `<-RP>`).
- Type‑number validity by context: LUNA `0–89,100–180`, PLC `90–93`, all `0–180`.

**Shared controller response/error strings** (host‑side protocol/diagnostic set):
`Controller check sum error`, `Controller ESC code error`, `Communication data error`,
`Controller timeout error`, `Controller send error`, `Program isn't in controller`,
`Program running error`, `Memory full`, `Memory error`, `None error history infomation`,
`Controller response error`, `Communication cable error`, `Send timeout error`,
`Receive timeout error`, `ESC code error`, `Check sum error`, `Data error`, `Program error`,
`File open error`, `File write error`, `File version error`, `PC memory error`,
`Type No. error`, `File name error`, `File kind error`, `Port number error`,
`Discompiler doesn't exist`.

**Per tool**

- **`SEND.EXE`** — uploads `.OBJ/.DAT/.CDT/.PLC/.COD`; extension map `.LUN .OBJ .PON .DAT .CPN
  .CDT .CTR .HEX .PLC .COD`; prompts `Transmitting file` / `Transmission complete`,
  `File exists. Execute?`.
- **`RECALL.EXE`** — downloads then optionally **decompiles** ("Do you discompile this file?"),
  chaining `ANNUL.EXE`, `DISPON.EXE`, `DPLC.EXE` (all three names embedded).
- **`FILES.EXE`** — prints the controller program directory: sections `SYSTEM PROGRAM`,
  `LUNA PROGRAM`, `PLC PROGRAM` with columns `TYPE NO. / FILE NAME(LUN|PON|PLC) / SIZE`, and a
  summary `%d program types. total %lu bytes(%.1f Kbytes). %.1f Kbytes free`.
- **`FDEL.EXE`** — deletes one type or `-A` all ("All files will be deleted. OK?").
- **`HIST.EXE`** — dumps the controller **error history** to `.HST`; embeds the complete
  axis/amp/servo fault taxonomy (see §5).
- **`MONIT.EXE`** — `Monitor program 5.0 (IBM-PC)`; serial terminal/monitor front‑end.
- **`INI_RS.EXE` / `INI_RS98.EXE`** — initialise the RS‑232 environment variables
  (`_port_number`, `_channel`, `PATH`) and the UART. `INI_RS98` is the NEC PC‑98 variant using
  `_pc98cominitx/_pc98comsendx/_pc98comrecvx/_pc98comsetstatx` BIOS calls, while `INI_RS` uses
  generic `_bios_serialcom`/`_int86`. The GUI invokes `INI_RS -P2` / `INI_RS98 -P2`.

### 3.3 Windows GUI — `SRXMONIE.EXE` ("SRX Platform")

- **Version resource:** `SRXMONI MFC `, `FileVersion 1.0.001`, `ProductName SRXMONI`, locale
  `0411 03A4` (Japanese/Shift‑JIS), MFC + VBX, links `KERNEL/USER/KEYBOARD/WIN87EM/COMMDLG/
  SHELL/DDEML`.
- **Frame classes:** `CMainFrame`, `CSrxmoniDoc/View`, plus a large MDI child set: `CLunaWnd`,
  `CPlcWnd`, `CIntWnd`, `CRealWnd`, `CPointWnd`, `CStringWnd`, `COutpWnd`, `CDatiWnd`,
  `CDatrWnd`, array variants, relay windows `CStdRlyWnd`, `CKeepRlyWnd`, `CTimerRlyWnd`,
  `CCounterRlyWnd`, `CInRlyWnd`, `COutRlyWnd`, `CSpecialRlyWnd`, `CLabelWnd`; plus
  `CRobotHereWnd` (current position), `CTaskStatusWnd`, `CErrWnd`.
- **Menus:** `File, Edit, Compile, Connection, Monitor, Send, System, Window, Help`. Key items:
  LUNNA/POINT/PLC editors, `POINT (PON to DAT)`, `Connect`, `Stop Communication`,
  `ON-LINE/OFF-LINE Set`, `LUNA Installation`, `LUNA Directory Set`, `Serial Port Set`,
  `Program Type Set`, `Error History`, `Robot/PLC/System/Peripheral Task Windows`, `I/O Windows`,
  `LUNA Variable Windows`, `PLC Relay Windows`, `Current Position`, `File Compile`, `SEND`,
  `RECALL`, `FILES`.
- **Editing/monitoring:** variable windows for INT/REAL/POINT/STRING/DATI/DATR/OUTP and array
  INT/REAL; point‑data editor (`Left/Right`, `Arm Form`, `Change Point`); online value change,
  breakpoints (`Line Pass`, `INT variable matching`), override (`Change Override Current/New %`),
  relay/bit monitor.
- **Built‑in messages** include the full operational/error dialogue set: servo‑ON, step‑stop,
  safety‑box/TP control arbitration, file‑too‑large limit **60 577 bytes**, online guards,
  RS‑232C framing/parity/overrun/DSR errors, compiler‑missing `LUNNA.EXE`/`PLC.EXE`,
  `ANNUL.EXE … Use version LUNA5.0E or later`.

### 3.4 Installer — `INSTALLE.EXE` ("Srxins v1.0")

MFC 16‑bit app (`CSrxinsDoc/View/MainFrame`); asks **DOS/V (IBM‑PC) vs PC‑98 (NEC)**, target
directory (default `SRXWIN\`), copies the platform files and creates the Windows program group
**SRX** containing `SRXMONIE.EXE`, `SRXMONIE.HLP`, `SRXMONI.ICO` and the PIFs. Version resource
`1.0.001`, locale Japanese.

---

## 4. File‑format map

| Extension | Meaning | Produced/consumed by |
|---|---|---|
| `.LUN` / `.LSF` | LUNA source / LUNA library source | LUNNA, ANNUL, LUNAPR |
| `.OBJ` | LUNA object code | LUNNA → controller; ANNUL ← |
| `.LIB` | LUNA library object | LUNNA |
| `.PON` / `.CPN` / `.MPN` | point / common‑data / memory‑card source | POINT, DISPON |
| `.DAT` / `.CDT` / `.MDT` | point / common / memory‑card data | POINT → controller; DISPON ← |
| `.PLC` / `.COD` | PLC source / PLC object | PLC, DPLC; controller |
| `.CTR` | Robot Data (parameters) | SEND/RECALL, GUI (`srxpara.ctr`) |
| `.KEE` | Keep‑relay data | SEND/RECALL, GUI (`srxrelay.kee`) |
| `.HEX` | raw download format | SEND |
| `.HST` | error history file | HIST |
| `.ERR` / `.BUF` / `.BAK` | compiler error / temp / backup | compilers |
| `.PIF` | DOS‑program shortcuts used by SRXMONIE | INSTALLE |

---

## 5. Cross‑links to the controller firmware

- **`HIST.EXE` fault taxonomy** is the same controller fault set documented for the firmware:
  LUNA object/system/robot/I‑O/point/parameter/array/integer/FOR/CALL‑nest/branch/interrupt/
  LN/SQRT errors; per‑axis robot/system/point limit errors; PLC code/CGET/CSET/BGET/BSET errors;
  emergency, axis and barrier limit sensors, TP/PC safety switches; the full SERVO/AMP/ABE fault
  list; RS‑232C channel diagnostics. Host‑side rendering of what the CPU board reports as `E nnn`.
- **`SRXMONIE.HLP` contains the complete error‑code guide** — contexts `E001…E359`, `E361`,
  `E381/E382`, `E4001…E4050`, `E4102`, `E4150/E4151`, `E4300…E4310`, `E4402/E4408`, plus compiler
  math codes `M6101…M6111`. The standalone manual ends at E400; the HLP is a useful comparison
  source (and includes E401 "DSS off", see `SRX-611_error_401_DSS_report.md`).
- **LUNA/PLC keyword tables** in LUNNA/ANNUL/PLC/DPLC are the host view of the firmware's
  `token_dispatch` table (`0xD99D2`) and LUNA/PLC engines — directly usable to resolve the
  firmware's "invalid jump table" token decode.
- **Serial framing** implied by the common message set (ESC code, checksum, byte‑count, timeouts)
  is the host side of the CPU board's serial/event task that raises error requests via
  `sys_req_27h`.
- **PLC special relays** (`ONLINE`, `SCAN`, `ERR`, `EMG`, `FIRST`, `CLK…`) map onto the firmware
  PLC engine (`plc_scan` @`0x4F020`, `plc_program_exec` @`0x4DFB8`).
- `SRX Platform5` model tags and HLP references to `SRX-H600`/`SRX-5x`/`SRX-60x` confirm
  applicability across the SRX‑5xx/6xx family, consistent with the firmware banners
  (SRX‑610/630).

---

## 6. Toolchain observations

- DOS tools: **Borland C++ (1991)** static runtime (`Divide error`, `Abnormal program
  termination`, `(null)`, `print scanf : floating point formats not linked`), `.EXE` real‑mode,
  built from `C:\L50\…` (later `B:\L50\…` for the PC‑98 build) — an internal Sony project tree
  ("L50").
- Windows tools: **MSVC 16‑bit MFC** with VBX support; version resources report `1.0.001`;
  `SRXMONIE` is the 1996 rewrite that replaces the earlier console workflow while still shelling
  out to the original DOS compilers.
- `LUNAPR.EXE` (1991, Turbo C++/lex) is the oldest surviving tool and predates the 1996 "5.0"
  suite.

---

## 7. Reverse‑engineering leads

1. `SRXMONIE.HLP` is a compressed Windows help file; its topic tree is intact and its embedded
   RTF (e.g. `hlp\afxmenue.rtf`) can be recovered to get the **full LUNA/PLC command reference**
   with numbers and examples.
2. `LUNNA.EXE`/`ANNUL.EXE` opcode tables can be diffed against `ROM1-C.bin`'s `0xD99D2` table to
   label every LUNA token with its exact spelling and argument grammar.
3. The common message module (`messg.c`) maps host error strings to numeric controller response
   codes — useful for annotating the firmware's error/event task and `sys_req_27h` call sites.
4. `INI_RS.EXE` documents the default serial line format used by the platform (the GUI hard‑codes
   `COM1:/COM2: 9600,n,8,2`), constraining the controller's ASCI/UART configuration.
5. `DPLC.EXE`/`PLC.EXE` LD‑style encoder tables (`R##C K##C T### C### I### L###`) mirror the
   firmware PLC compiler/scan data model.

---

## 8. Integrity (MD5)

```
ANNUL.EXE      aa444e060f809cfe20ea703a05b66a29     FILES.EXE      4973b97ee0bfed63580d44c768619b77
DISPON.EXE     7472579b97cc8a9c4474473615abde3e     HIST.EXE       a6ec1bc7b4b655174dfe7e60b7ee58bb
DPLC.EXE       d5b949dffddb5a11ab47755d54f20020     INI_RS.EXE     4a4722cbaab7112b00dc9ad4fef2ee11
FDEL.EXE       a40dc3e5951d014ac3fdaf6048df0a88     INI_RS98.EXE   9e803c2f7639a7ccad376ce17901d8ec
INSTALLE.EXE   90579a37e48df6253e72344788bd2631     LUNAPR.EXE     ea5479f62110e786945be9ed7e6e67eb
LUNNA.EXE      eabbc3f0ca01b733cbd37c0efd11919c     MONIT.EXE      30b88ef336cd4ca42e01b223b6965716
PLC.EXE        10bf67fa31f89cb6ab6c03b208555214     POINT.EXE      653a5990ced73a77119ab9a3a6545724
RECALL.EXE     44663db7a68ac50f479d9e3afcd1341e     SEND.EXE       27fac6b3deb840c4e75da228d78eed45
SRXMONI.ICO    d074da74be8627c1e6ccf96645bc7f50     SRXMONIE.EXE   bc038614fc555304c51202e60b8f9579
SRXMONIE.HLP   832575a4ff730cbbd452a9f828c31d79
```

---

**Summary.** SRXWIN is the complete Sony host toolchain for the SRX‑5xx/6xx controller — a
Borland‑C DOS compiler/communication suite (`LUNNA/POINT/PLC` compilers, `ANNUL/DISPON/DPLC`
decompilers, `SEND/RECALL/FILES/FDEL/HIST/MONIT`, `INI_RS/98`, `LUNAPR`) wrapped by a 1996 MFC
"SRX Platform" GUI (`SRXMONIE`) and installed by `INSTALLE`. It is the best available host‑side
reference for the firmware's LUNA/PLC token sets, file formats, serial protocol, error codes and
parameter/point data model.
