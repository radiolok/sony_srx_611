# SRX controller ↔ PC serial protocol (reversed from SRXWIN)

**Scope:** the RS-232C protocol spoken between the Sony SRX-5xx/6xx controller (SRX-611,
"PROGRAMMING UNIT" port) and the SRXWIN host tools in `SRXWIN/`.
**Sources:** static disassembly of the DOS utilities `FDEL.EXE`, `FILES.EXE`, `SEND.EXE`,
`RECALL.EXE`, `HIST.EXE`, `MONIT.EXE`, `INI_RS.EXE` (Borland C++ 1991, large model), and a
frame-builder scan of `SRXMONIE.EXE` (Win16/MFC). The status-code names come from
`SRXMONIE.HLP` (see [`SRXMONIE_help.md`](SRXMONIE_help.md), section "SRX platform error").
**Status:** static analysis only — **nothing here has been confirmed on hardware**. The
controller-side implementation was located in `ROM1-C.bin` and agrees with the host side (§9). Addresses
are file offsets inside the loaded MZ image (after the MZ header) unless stated otherwise.
**Companion docs:** [`SRXWIN_tools_report.md`](SRXWIN_tools_report.md) (tool inventory),
[`SRXWIN-NG.md`](SRXWIN-NG.md) (replacement spec; its §8 safety rules apply to any test of
this protocol against a real controller).

---

## 1. Summary

| Item | Value | Evidence |
|---|---|---|
| Host ports | COM1 (`3F8h`) or COM2 (`2F8h`) only (`rs_open` rejects anything else) | FDEL `0x44E8`, `0x47CA` |
| Line format | **9600 baud, 8 data bits, no parity, 2 stop bits** | every tool calls `rs_open(port, 9600, 8, 2, 0)`; SRXMONIE strings `COM1:9600, n, 8, 2` |
| Modem lines | Host raises **DTR + RTS**; it only transmits while **DSR** is high | FDEL `0x460F` (`int 14h AH=05h` MCR \|= 3), `0x470F` (status bit `20h`) |
| Framing | `1B LEN CMD … SUM`, binary, LEN = whole frame length | §2 |
| Checksum | 8-bit sum of all bytes before the checksum byte | FDEL `0x43F5` / `0x441C` |
| Flow | Strict request → reply, one frame at a time, no retries | all command routines |
| Per-byte timeout | 0x5B BIOS ticks ≈ **5.0 s** (for both TX-ready and RX-ready) | FDEL `0x46E9`, `0x4781` |
| Data block | ≤ **128** payload bytes per `02`/`04` frame | SEND `0x3838` |
| Second channel use | Same port also carries a plain ASCII monitor console (MONIT) | §7 |

---

## 2. Frame format

```
request : 1B  LEN  CMD  arg…                SUM
reply   : 1B  LEN  xx   STATUS  payload…    SUM
          [0] [1]  [2]  [3]     [4..LEN-2]  [LEN-1]
SUM = (byte[0] + byte[1] + … + byte[LEN-2]) & 0xFF
```

* `LEN` counts **every** byte of the frame, including the leading `1B` (ESC) and the checksum.
* Multi-byte integers are **little-endian**.
* Host receive procedure (identical in every tool): read 2 bytes; if byte 0 ≠ `1B` → host
  error 1023 "ESC code error"; read `LEN-2` more bytes; verify checksum (→ 1024 "Check sum
  error"); then test `STATUS` (byte 3).
* Reply byte 2 is never checked by the host. It is the echo of `CMD` (confirmed on the controller side, §9.1).
* Worked example — delete LUNA program type 3 (kind `5C`):
  `1B 06 06 03 5C 86` (sum 1B+06+06+03+5C = 86h).

### 2.1 Status byte and error numbering

`STATUS = 0` means success. A non-zero status `s` is the controller-side error that the
SRX Platform GUI reports as **E(4000+s)** (list from `SRXMONIE.HLP`). The DOS tools map a
subset onto their own message numbers (FDEL `0x4447`):

| s | HLP code / text | DOS tool message (code) |
|---|---|---|
| 1 | E4001 SEND check sum error | Controller check sum error (1000) |
| 2 | E4002 SEND ESC code error | Controller ESC code error (1001) |
| 3 | E4003 Command number error | Communication data error (1002) |
| 4 | E4004 SEND size error | Communication data error (1002) |
| 5 | E4005 SEND time out error | Controller timeout error (1003) |
| 6 | E4006 SEND execute error | Controller send error (1004) |
| 7 | E4007 RECALL block receive error | Communication data error (1002) |
| 8 | E4008 No program error | Communication data error (1002) |
| 9 | E4009 Program kind error | Communication data error (1002) |
| 10 (`0A`) | E4010 No task program error | Program isn't in controller (1005) — treated as "empty slot" by FILES and as success by FDEL |
| 11 | E4011 Program executing error | Program running error (1006) |
| 12 | E4012 Program memory area error | Memory full (1007) |
| 13 | E4013 Program memory error | Memory error (1008) |
| 14 | E4014 Task error | Communication data error (1002) |
| 15 | *(not in HLP)* | None error history information (1009) — ends the HIST loop |
| other | E4020…E4050, E4102, E4150/E4151 (variables, breakpoints, PLC relays, ON-LINE, TP master, safety box, mode, emergency…) | Controller response error (1010) |

Host-side errors (not sent on the wire): DOS 1020 "Communication cable error" (DSR low),
1021 send timeout, 1022 receive timeout, 1023 ESC error, 1024 checksum error, 1025 data
error, 1030–1039 file/argument errors. The GUI equivalents are E4300–E4310 (RS-232C
framing/DSR/overrun/…), and E4402/E4408 are compiler errors.

---

## 3. Program addressing: *type* and *kind*

Every file command carries a **type** (program/task slot number) and a **kind** byte.

| Kind | File | Host extension | SEND/RECALL switch | Notes |
|---|---|---|---|---|
| `5A` | Common data | `.CDT` (source `.CPN`) | `-RC` | |
| `5B` | Controller data (robot parameters) | `.CTR` | `-D` (inferred from flag test) | |
| `5C` | LUNA object | `.OBJ` (source `.LUN`) | `-RO` / `-RA` | file header has a second size field (§4.4) |
| `5D` | Point data | `.DAT` (source `.PON`) | `-RD` / `-RA` | |
| `5E` | PLC object | `.COD` (source `.PLC`) | `-RP` | types 90–93 (the delete-all path also uses 0–3) |
| `5F` | "SYSTEM PROGRAM" | `.OBJ` | — | forced whenever type = 100 (`0x64`) |

Type ranges shown by the tools: LUNA 0–89 and 100–180, PLC 90–93, and system program 100.
FILES, FDEL and SEND usage texts limit robot/peripheral programs to types **0–15**
(`-T<0~15>`). FILES groups its listing as SYSTEM PROGRAM / PLC PROGRAM / LUNA PROGRAM.

---

## 4. Command reference (DOS utilities)

### 4.1 `05` — directory query (FILES, FDEL)

```
req : 1B 06 05 type kind SUM
rep : 1B LEN xx 00 attr size32 name… 00 SUM      (entry present)
      1B LEN xx 0A …                              (slot empty)
```
`attr` (+4) is copied but its meaning is unknown. The host marks "absent" with `FF`.
`size32` is at +5 and `name` at +9 (NUL-terminated). FDEL `0x3489`.
A full directory scan (FDEL `0x33BB`, FILES) queries `(5F,0)`, then `(5E,0..3)`, then
`(5C,t)` and `(5D,t)` for t = 0..15.

### 4.2 `06` — delete (FDEL)

```
req : 1B 06 06 type kind SUM          rep : status 00 or 0A = OK
```
Per-type kinds (FDEL `0x3128`):
* `-A`: `(5F,0)`, `(5E,0..3)`, then `(5C,t)`/`(5D,t)` for t = 0..15.
* type 90–99: `(5E,type)`.
* type 100: `(5F,100)` then `(5D,100)`.
* anything else: `(5C,type)` then `(5D,type)`.

Each delete is preceded by a `05` existence check.

### 4.3 `01`/`02` — download a file to the controller (SEND)

```
start : 1B 13 01 type kind total32 name[8] ?? SUM          (LEN 19)
data  : 1B n+9 02 type kind block16 last data[n] SUM        (n ≤ 128)
reply : 1B LEN xx STATUS … SUM                              (after every frame)
```
* `total32` = size1 + size2 (§4.4), and `name[8]` is copied from file-header bytes 4..11.
  Byte 17 of the start frame is **never initialised** by SEND.EXE (stack garbage, but still
  covered by the checksum). A re-implementation should send `00`.
* `block16` starts at 1 and increments per frame. `last` = 1 on the final frame (≤ 128 bytes
  remaining), otherwise 0.
* The payload is the first `size1` bytes of the file (from its start, header included),
  followed by `size2` bytes from the second part (kind `5C` only). SEND `0x36B4`.
* If type = 100, kind is forced to `5F`.

### 4.4 `04` — upload a file from the controller (RECALL)

```
req : 1B 08 04 type kind block16 SUM
rep : 1B LEN xx STATUS last data[LEN-6] SUM
```
* RECALL first asks for **block 1** to read the file header (RECALL `0x4B0D`), then reads
  blocks 1, 2, … until `size1 + size2` bytes have arrived (RECALL `0x4969`). If the final
  block does not carry `last = 1`, the transfer fails with 1002.
* File header (first bytes of block 1 = first bytes of the file):

  | Offset | Size | Field |
  |---|---|---|
  | 0 | 1 | kind (`5A`…`5F`) |
  | 2 | 2 | size1 |
  | 4 | 8 | name, space-padded |
  | 12 | 2 | size2 (**kind `5C` only**; 0 otherwise) |

### 4.5 `15` / `14` — error history (HIST)

```
15: req 1B 04 15 SUM          rep: status + 9 bytes (+4..+12)
14: req 1B 05 14 idx SUM      rep: status + record (see below), idx = 0..19
```
* HIST reads records 0..19 and stops at the first status 15 ("no history").
* It calls `15` only with `-F` (save to file). The 9 returned bytes become the default
  `<name>.HST` base name, which suggests an 8-character ID + NUL (inferred).
* Record layout (HIST `0x3215`, printed as `E%4d%7d%5d%5d%6d%4d  %s` = error task line
  year month day text):

| Reply offset | Size | Field |
|---|---|---|
| +4 | u16 | error code `E nnn` (indexes HIST's own 600-entry message table) |
| +6 | u8 | task |
| +7 | u16 | LUNA line |
| +9 | u16 | year |
| +11 | u8 | month |
| +12 | u8 | day |
| +13..+15 | u8×3 | not printed; probably hour, minute, second (inferred) |

HIST's built-in error-text table (DS `0x94`, 8-byte JP/EN far-pointer pairs) has 121
non-empty entries, E000–E390. It has **no E400/E401**, and 17 newer firmware messages
(memory card, CP motion, encoder copy/homing, SPD over-speed, DSS off) are missing. This
matches a 1996 toolchain predating the SMART option.

---

## 5. Host serial driver (shared `rsfnc.c`, FDEL segment `0x44E`)

| Routine | FDEL addr | Behaviour |
|---|---|---|
| `rs_open(port, baud, bits, stop, parity)` | `0x44E8` | port 1/2 → COM1/COM2. Baud table 110…9600, bits 7/8, stop 1/2, parity 0 none/1 odd/2 even. `bioscom(0,…)` then `int 14h AH=05h`: read MCR, write MCR \| 3 (DTR+RTS). Errors 10000–10004 |
| `rs_rx_ready(&flag)` | `0x4664` | `bioscom(3)` status, AH bit 0 = data ready |
| `rs_flush()` | `0x4697` | drain receiver |
| `rs_putc(c)` | `0x46C8` | 500-iteration busy delay, then wait ≤ 5 s for DSR (AL bit 5). If DSR never rises → 10007 (= "cable error" 1020). Then `bioscom(1,c)`. Timeout → 10006 |
| `rs_getc(&c)` | `0x4769` | wait ≤ 5 s for data ready, then `in al, dx` **directly from RBR** (`3F8h`/`2F8h`). Timeout → 10006 |
| `rs_write(n, buf)` / `rs_read(n, buf)` | `0x47EB` / `0x4820` | byte loops |
| `frame_set_sum(buf)` / `frame_check_sum(n, buf)` | `0x43F5` / `0x441C` | 8-bit additive checksum |
| `status_to_msg(s, &code)` | `0x4447` | §2.1 mapping |

Implications for a modern re-implementation (SRXWIN-NG `srx-link`):
* The USB-RS232 adapter and cable **must carry DSR** and should assert DTR/RTS.
* The protocol has no sequence acknowledgement beyond the per-frame reply, and no retries.
  A lost reply surfaces as a 5 s timeout.
* 9600 8N2 is hard-coded in every DOS tool. Whether the controller accepts other rates is
  unknown.

---

## 6. SRXMONIE (SRX Platform GUI) command set

The GUI links its own copy of the protocol (it does **not** call the DOS tools for
monitoring). A scan of `SRXMONIE.EXE` for frame builders (`mov byte [bp-x], 1Bh` followed by
LEN and CMD stores) found **~110 commands**, `01`–`A6`. The DOS-tool commands `01 02 04 06 14`
reappear with identical layouts. The rest are the online-debugging/monitoring commands
behind the GUI's variable windows (INT/REAL/POINT/STRING/DATI/DATR/OUTP, arrays), relay
windows (standard/keep/timer/counter/input/output/special), breakpoints ([BK1]/[BK2]),
step/execute controls, ON-LINE/OFF-LINE and point data. The E4020–E4044 status names
(value number, axis number, breakpoint line/INT/count, PLC breakpoint relay, special relay
number, ON LINE, TP master, mode, teach mode…) are the controller's replies to these.

**Command names are not yet resolved.** Mapping each builder to its GUI caller needs NE
relocation analysis (next step). The table gives the raw request layout: offsets are from
the frame start, `u8`/`u16` are caller-supplied arguments, and bytes filled by copy loops
(names, strings, point data) are not captured.

| Cmd | Req. LEN | Request argument bytes (after `1B LEN CMD`) | Known meaning | Builder @file |
|---|---|---|---|---|
| `01` | 19 | +3 u8, +4 u8, +5 u16, +7 u16 | SEND start (as SEND.EXE) | `0x04884B` |
| `02` | n+9 | +3 u8, +4 u8, +5 u16, +7 u8 | SEND data block (as SEND.EXE) | `0x0488E3` |
| `04` | 8 | +3 u8, +4 u8, +5 u16 | RECALL block (as RECALL.EXE) | `0x04896C` |
| `06` | 6 | +3 u8, +4 u8 | delete program (as FDEL.EXE) | `0x048A07` |
| `07` | 6 | +3 u8, +4 u8 |  | `0x048798` |
| `08`–`0B` | 6 | +3 u8, +4 u8 |  | `0x04A08C`–`0x04A220` |
| `0C`–`10` | 4 | — (no arguments) |  | `0x04A2B0`–`0x04A40F` |
| `11` | 6 | +3 u16 |  | `0x04A456` |
| `12` | 7 | +3 u8, +4 u8, +5 u8 |  | `0x04A4E1` |
| `13` | 7 | +3 u8, +4 u16 |  | `0x04A5EA` |
| `14` | 5 | +3 u8 | read error-history record (as HIST.EXE) | `0x048A4D` |
| `16` | 7 | +3 u8, +4 u16 |  | `0x04A6B1` |
| `17`, `18` | 7 | +3 u8, +4 u8, +5 u8 |  | `0x04A6F9`, `0x04A747` |
| `19`, `1A` | 6 | +3 u8, +4 u8 |  | `0x04A795`, `0x04A7DD` |
| `1C`–`1F` | 4 | — |  | `0x04A86D`–`0x04A921` |
| `20` | 6 | +3 u16 |  | `0x04A95D` |
| `21`–`23` | 4 | — |  | `0x04A99F`–`0x04AA17` |
| `24` | 5 | +3 u8 |  | `0x04AA5D` |
| `25` | 11 | +3 u8, +4 u8, +5 u8, +6 u8, +7 u8, +8 u16 |  | `0x04AAD1` |
| `26`–`28` | 5 | +3 u8 |  | `0x04AB33`–`0x04ABB7` |
| `29` | 4 | — |  | `0x04AC03` |
| `30`, `33`, `38` | 7 | +3 u8, +4 u8, +5 u8 |  | `0x048AD8`, `0x048C74`, `0x048EF1` |
| `31` | 8 | +3 u8, +4 u8, +5 u16 |  | `0x048B63` |
| `32`, `35`, `36`, `39`, `3A`, `3C`, `43`, `45`, `46` | 6 | +3 u8, +4 u8 |  | `0x048BB2` … `0x04956C` |
| `34` | 14 | +3 u8, +4 u8, + copied data |  | `0x048D04` |
| `37` | 15 | +3 u8, +4 u8, +5 u8, + copied data |  | `0x048E9A` |
| `3B`, `47` | 7 | +3 u8, +4 u16 |  | `0x049087`, `0x0495F1` |
| `3D` | 13 | +3 u8, + copied data |  | `0x04915A` |
| `3E`, `42` | 7 | +3 u8, +4 u8, +5 u8 |  | `0x0491A9`, `0x04933F` |
| `3F` | 16 | +3 u8, +4 u8, +5 u8, +6 u8, + copied data |  | `0x049230` |
| `40` | 8 | +3 u8, +4 u8, +5 u8, +6 u8 |  | `0x049293` |
| `41`, `48`, `49`, `4A`, `4C`–`51`, `53`, `59`, `5D`, `73`, `A6` | 5 | +3 u8 |  | `0x0492E7` … `0x04A010` |
| `44` | n+8 | +3 u8, +4 u8, +5 u8, + data |  | `0x04942D` |
| `4B`, `54`–`57`, `5A`, `5E`, `72`, `80`, `81` | 6 | +3 u8, +4 u8 |  | `0x04971D` … `0x049F14` |
| `58` | 16 | +3 u8, +4 u8, +5 u8, +6 u16, +8 u8, +9 u16, +11 u16, +13 u16 |  | `0x049A8D` |
| `5B`, `5F` | 15 | +3 u8, +4 u8, + copied data |  | `0x049BB6`, `0x049DF4` |
| `5C` | 16 | +3 u8, +4 u8, + copied data |  | `0x049C60` |
| `60` | 22 | +3 u8, +4 u8, + copied data |  | `0x049EA4` |
| `61`, `63`, `64`, `66`, `68`, `69`, `6B`, `6C`, `6F`, `71` | 4 | — |  | `0x048277` … `0x048728` |
| `65` | 7 | +3 u16, +5 u8 |  | `0x0483A1` |
| `67`, `6A` | 8 | +3 u16, +5 u8, +6 u8 |  | `0x04847B`, `0x04858F` |
| `6D`, `6E`, `7C`–`7F` | 5 | +3 u8 |  | `0x048667` … `0x04951F` |
| `79` | 3·n+5 | +3 u8 count, then n × 3-byte items |  | `0x04A53A` |
| `7B` | 7 | +3 u8, +4 u16 |  | `0x04A669` |

Not present in SRXMONIE: `05` (directory query) and `15` (history ID); the GUI spawns
`FILES.EXE`/`HIST.EXE` for those. The raw per-builder list is reproducible with
`tools/srxwin/srxmonie_cmds.py`.

---

## 7. MONIT — ASCII monitor console

`MONIT.EXE` ("Monitor program 5.0 (IBM-PC)") opens the same port at 9600 8N2 and acts as a
dumb terminal (MONIT `0x3476`):
* It echoes every received byte to the screen.
* It sends every keystroke; **CR is sent as CR LF**.
* **ESC** quits locally and is not transmitted.

So the controller's programming port also has a text console. Its command set is not in the
PC tools (it lives in the controller firmware).

---

## 8. Open points / next steps

1. **Confirm on hardware** with the original tools under DOSBox-X/86Box plus a serial sniffer.
   Check the `attr` byte of `05`, the time fields of `14`, and the `15` payload.
2. Resolve SRXMONIE command names. Two routes: NE relocation analysis of `SRXMONIE.EXE`, or
   naming the firmware handlers `host_cmd_XX` in Ghidra (§9); the firmware side is now easier.
3. Name the ~40 firmware-only commands (§9.3). They are not used by any SRXWIN tool and are
   probably later additions (a newer host tool, or production/service use).
4. Identify the peer on OS channel `0x10001` (§9.4).
5. Record several real `.OBJ/.DAT/.CDT/.COD/.CTR` files to confirm the §4.4 header layout.

---

## 9. Controller side (ROM1-C.bin)

Located 2026-09-26 by searching the 32-bit image for `1Bh` checks and then matching status
values. The analysis is in Ghidra (`tools/ghidra/`, program based at `0xFFE00000`, labels
applied by `LabelSrxProtocol.java`). Addresses are **file offsets** (runtime = `0xFFE00000` +
offset).

### 9.1 Receive path and server task

| File offset | Ghidra label | Role |
|---|---|---|
| `0x50D00` | `host_cmd_server_task` | Task entry (no direct callers; started by the OS). Configures OS serial channel **`0x10002`** (two `ioctl`-style calls via `0xCE53B`, value 200), then loops forever |
| `0x50EA8` / `0x50F78` | `host_rx_wait_frame` / `host_rx_frame_body` | Read a frame into the request block; return 5 on timeout (the task then calls `0x55CE8` if a transfer is in progress and keeps waiting) |
| `0x51180` | `host_rx_frame` | Stand-alone frame reader. Timeout → **5**, byte 0 ≠ `1B` → **2**, LEN ≤ 4 → **4**, checksum mismatch → **1**, OS error → **100** |
| `0x51088` | `host_rx_frame_retry` | `host_rx_frame` with up to 3 attempts. On a checksum error it sends `1B 05 cmd 01 SUM` and retries (the DOS tools themselves never retry) |
| `0x512A0` | `host_send_reply` | Checksum + write a handler-built reply on channel `0x10002` |
| `0x51328` | `frame_set_checksum` | `byte[LEN-1] = Σ byte[0..LEN-2]` |
| `0x51828` | `host_cmd_table` | **172 (`0xAC`) × 32-bit absolute handler pointers**, indexed by the command byte |
| `0x51360` | `host_cmd_unknown` | Default entry (20 unused slots) |

Server loop (from Ghidra's decompilation):
```c
for (;;) {
    wait for and read a frame into req;            // status 5 = timeout, keep waiting
    if (req.cmd >= 0xAC) st = 3;                     // E4003 "Command number error"
    else st = host_cmd_table[req.cmd](&req);         // 0 = handler already replied
    if (st) {
        if (st > 0xFF) { sys_req_27h(0, st, 0x1E); st = 100; }   // internal error -> log + 100
        send(1B 05 req.cmd st SUM);                  // generic status-only reply
    }
}
```
The request block stores the command at `+0`, LEN at `+1`, and the raw frame from `+2`
(`1B LEN CMD a0 a1 …`). A handler checks `+1` against the expected LEN, reads its arguments
at `+5…`, and builds its reply in the same buffer. **Reply byte 2 is therefore the command
echo**, which §2 had left unverified.

### 9.2 Cross-check: `host_cmd_06` (delete, `0x56070`)

```
if busy-flag (+0x104) == 1 -> 6          E4006 SEND execute error
if LEN != 6              -> (size error path)
type = +5, kind = +6 ; lock(kind); look up; delete; unlock
  lookup  0x36BA -> 8   E4008 No program error
  lookup  0x36BC -> 10  E4010 No task program   (FDEL treats 10 as "already deleted")
  kind    0x36BB -> 9   E4009 Program kind error
  delete fails   -> 13  E4013 Program memory error
  success: reply 1B 05 06 00 SUM
```
This matches both the DOS-side mapping (§2.1) and the HLP names exactly.

### 9.3 Command table coverage

All ~110 commands used by SRXMONIE and the DOS tools (`01`–`A6`, incl. `05` and `15`) have a
handler. The table also has handlers that **no SRXWIN tool sends**:
`03 1B 2A–2F 52 62 70 74–78 7A 82–84 96–9D A0–A5 A7–AB`. The 20 unassigned slots
(→ `host_cmd_unknown`) are `00`, `85–95`, `9E` and `9F`.

Handler families, grouped by shared callees. The "likely area" column is a guess until the handlers are read:

| Commands | Handler range | Common callees | Likely area |
|---|---|---|---|
| `01 02 04 05 06 07` | `0x55688`–`0x561C8` | program store (`0x12514`/`0x125BC` lock/unlock, `0x13E1C` lookup, `record_get_field*`) | file transfer / directory / delete |
| `08`–`0E`, `11 12 16`–`29`, `2B`–`2F` | `0x56418`–`0x58060` | `0xC2xxx`–`0xC5xxx` (LUNA variable/format cluster) + `0x51370` (generic value reply) | LUNA variable read/write (monitor windows) |
| `14 15` | `0x56310`, `0x563C0` | `0xBE174` / `0xAA14` | error history |
| `30`–`60` | `0x51AD8`–`0x54450` | `0x25xxx`–`0x28xxx`, `0x59xxx` | PLC relays / channels / breakpoints (by the GUI's relay windows) |
| `61`–`71` | `0x58350`–`0x58F18` | | task control (run/stop/step, likely) |
| `96`–`AB` | `0x54A70`–`0x555C8` | | not used by SRXWIN |

### 9.4 Second ESC-framed link: OS channel `0x10001`

`0xBB5EC` (IDA name `db_access`, labelled `peer_request` in Ghidra) is **not** a database
accessor. It is the *client* side of the same framing on a different serial channel:
1. Flush.
2. Write the `1B LEN CMD …` frame.
3. Read the `1B` byte and LEN, then the rest of the reply.
4. Return errors `0xA11`/`0xA12`/`0xA16`/5.

About 37 small builders at `0xBA365`–`0xBB4FA` (IDA names `db_field_N`, `db_get_field92`…)
each assemble one command (e.g. `1B 05 20 …`, `1B n+3 41 <string>`) and convert a
non-zero reply status `s` to `20000 + s`. The IDA "field id" in those names is really a
**command code on that link**.

**Update 2026-09-26: the peer is the teach pendant.** The TP task (`0x62A54`) opens the channel
(`0xBB57C`) and sends `1B 07 01 'SRX6'` (`0xBA35C`), then checks for `'TP4'` in the reply.
That is the handshake the TP firmware implements (`doc/TP_firmware_structure.md` §6). This link
carries **no checksum**. All 38 command codes the CPU uses appear in the TP dispatcher. The command
table (CPU builder, TP handler, call counts, meaning) is in
[`SRX-611_firmware_architecture.md`](SRX-611_firmware_architecture.md) §8.1.
