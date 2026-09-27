# PROTOCOL.md — SRX host link (normative spec for `srx_link`)

Evidence and addresses: [`doc/SRXWIN_protocol.md`](../../../doc/SRXWIN_protocol.md) (host
side, SRXWIN EXEs) and its §9 (controller side, `ROM1-C.bin`). This file states only
what `srx_link` and `srx_fake` implement.

**Status tags** (spec §5.4):
- **[H]** hypothesis: seen in a disassembler.
- **[E]** confirmed against the original DOS tool running in DOSBox-X with `srx_fake`
  (`tests/test_dosbox_oracle.py`). This proves the host side, not the controller.
- **[C]** confirmed on the real controller. Nothing has this tag yet.

## 1. Line

| Item | Value | Status |
|---|---|---|
| Rate / format | 9600 baud, 8 data bits, no parity, 2 stop bits | [H] |
| Host modem lines | host raises DTR + RTS after opening the port | [E] (nullmodem control byte `03`) |
| Host TX gate | host sends a byte only while DSR is high; waits ≤ 5 s, then "cable error" | [H] |
| Per-byte timeout | ≈ 5 s for both TX and RX | [H] |

## 2. Frame

```
request : 1B LEN CMD arg…              SUM
reply   : 1B LEN CMD STATUS payload…   SUM
SUM     = (sum of all bytes before SUM) & 0xFF
```
- `LEN` counts every byte, including `1B` and `SUM`. The minimum reply is 5 bytes. [E]
- Integers are little-endian. [E]
- Reply byte 2 echoes `CMD`. The host tools ignore it; `srx_link` checks it and logs a
  mismatch as a warning. [H, controller side]
- Strictly one request, then one reply. The host never retries. [E]
- The controller retries a bad-checksum request up to 3 times, replying `1B 05 CMD 01 SUM`. [H]

## 3. Status byte

`0` = OK. Non-zero `s` is the GUI error **E(4000+s)**. The names below come from
`SRXMONIE.HLP`, and `srx_link.errors` maps each one to a typed exception.

| s | name | exception |
|---|---|---|
| 1 | SEND check sum error | `ChecksumError` |
| 2 | SEND ESC code error | `EscCodeError` |
| 3 | Command number error | `CommandNumberError` |
| 4 | SEND size error | `SizeError` |
| 5 | SEND time out error | `ControllerTimeoutError` |
| 6 | SEND execute error | `ExecuteError` (controller busy with a transfer) |
| 7 | RECALL block receive error | `BlockError` |
| 8 | No program error | `NoProgramError` |
| 9 | Program kind error | `ProgramKindError` |
| 10 | No task program error | `EmptySlotError` (FILES = "empty", FDEL = success) |
| 11 | Program executing error | `ProgramRunningError` |
| 12 | Program memory area error | `MemoryFullError` |
| 13 | Program memory error | `MemoryError_` |
| 14 | Task error | `TaskError` |
| 15 | (no HLP text) end of error history | `NoHistoryError` |
| other | E4020… (monitoring commands) | `ControllerError` |

## 4. Addressing

`type` = program slot (LUNA 0–89 and 100–180, PLC 90–93; the DOS tools use 0–15).
`kind`:

| kind | file | note |
|---|---|---|
| `5A` | `.CDT` common data | |
| `5B` | `.CTR` robot parameters | **WRITE blocked** (spec §8) |
| `5C` | `.OBJ` LUNA object | has `size2` |
| `5D` | `.DAT` point data | |
| `5E` | `.COD` PLC object | |
| `5F` | system program `.OBJ` | forced when type = 100 |

## 5. File header (every transferable file)

| off | size | field | status |
|---|---|---|---|
| 0 | u8 | kind | [E] (LUNNA/POINT output) |
| 1 | u8 | 0 | [E] |
| 2 | u16 | size1 = code part | [E] |
| 4 | 8 | name, space-padded ASCII | [E] |
| 12 | u16 | size2 = table part (`5C` only) | [E] |

Transferred length = `size1 + size2` (kind `5C`), otherwise `size1`. LUNNA and POINT
output ends with `0xED`, which is included in that length. [E]

## 6. Commands (DOS-tool set)

Danger class per spec §8: **R** = READ, **W** = WRITE.

| cmd | class | request | reply payload after STATUS |
|---|---|---|---|
| `05` dir | R | `1B 06 05 type kind SUM` | `type u8` [E: FILES prints it], `size u32` [E], `name` ASCIIZ [E]; status 10 = empty [E] |
| `06` delete | W | `1B 06 06 type kind SUM` | none; 0 or 10 = OK [E] |
| `01` send start | W | `1B 13 01 type kind total u32, name[8], pad SUM`; pad = `00` (QUIRK: SEND.EXE leaves stack data) [E] | none [E] |
| `02` send block | W | `1B n+9 02 type kind block u16, last u8, data[n] SUM`, n ≤ 128, block from 1 [E] | none [E] |
| `04` recall block | R | `1B 08 04 type kind block u16 SUM` [E] | `last u8, data[LEN-6]` [E] |
| `15` history ID | R | `1B 04 15 SUM` | 9 bytes (8-char ID + NUL?) [H] |
| `14` history rec | R | `1B 05 14 idx SUM`, idx 0..19 [E] | `code u16, task u8, line u16, year u16, month u8, day u8` [E: HIST prints them], `h m s u8` [H]; status 15 = end [E] |

Host sequences [E] (reproduced by `Session`):
- FILES: `05` for `(0,5F)`, `(0..3,5E)`, then for t = 0..15 `(t,5C)`, `(t,5D)`.
- SEND: `01` then `02` blocks. With type 100 the kind becomes `5F`.
- RECALL: block 1, then blocks 1..N (QUIRK: block 1 twice), per kind; `-RA` = `5C`, `5D`.
- FDEL `-T n`: `06 (n,5C)`, `06 (n,5D)`; [H] 90–99 → `(n,5E)`, 100 → `(100,5F)`, `(100,5D)`.
- HIST: `14` idx 0.. until status 15 (`15` is sent only with `-F`).

## 7. Session rules (`srx_link.Session`)

- Every command has a danger class. `Session` refuses WRITE unless `allow_write=True`.
  It refuses a WRITE to kind `5B`/`.KEE` unconditionally, and refuses MOTION unless
  `allow_motion=True`.
- Every byte is journalled as JSON Lines: `{"t": seconds, "dir": "tx"|"rx", "hex": "..."}`.
  The journal can be replayed with `ReplayTransport`.
- Commands not listed in §6 may be sent only to `srx_fake` (spec §8.1: no protocol
  fuzzing on hardware).

## 8. DOSBox-X nullmodem wire format (test harness only)

With `serial1=nullmodem server:HOST port:N` (non-transparent), DOSBox-X connects to
`srx_fake` over TCP. Data byte `FF` is sent as `FF FF`. `FF x` is a control-line update:
bit 0 = RTS, bit 1 = DTR, bit 2 = break (guest → us); our `FF x` sets the guest's
CTS (bit 0) and DSR (bit 1). `srx_fake` sends `FF 03` after the connection opens. [E]
