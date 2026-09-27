# FORMATS.md — SRX program files (FMT-*)

Status tags as in [PROTOCOL.md](PROTOCOL.md). **[E]** here means "seen in output of the
original compiler" (`corpus/golden/`).

## 1. Common header (all transferable files)

| off | size | field | status |
|---|---|---|---|
| 0 | u8 | kind `5A`–`5F` | [E] |
| 1 | u8 | 0 | [E] |
| 2 | u16 LE | size1 | [E] |
| 4 | 8 | name, ASCII, space-padded (= source base name) | [E] |
| 12 | u16 LE | size2, kind `5C` only | [E] |

- The file length equals `size1 + size2` for `.OBJ` and `size1` for `.DAT`.
- The last byte is `0xED` (end mark, not a checksum) in LUNNA and POINT output. [E]

## 2. `.OBJ` (LUNA object, kind 5C)

`T1.LUN` (`INT : CNT,VAL` / `CNT=1` / `VAL=CNT+2` / `DO P0(1)` / `END`) compiles to
size1 = 80 ("Object code 80 bytes") and size2 = 34 ("Table object code 34 bytes"). The
table part ends with the symbol names (`03 'CNT' 03 'VAL'`, length-prefixed). The code
part is not decoded yet; see `doc/LUNA_token_map.md`.

## 3. `.DAT` (points, kind 5D)

`T1.PON` with `P0(1)=100.0,200.0,10.0,0.0` gives 35 bytes:

```
5D 00 23 00 'T1      ' 00 01 80 00 00 00 | A0 86 01 00 | 40 0D 03 00 | 10 27 00 00 | 00 00 00 00 | 00 00 ED
```
- The coordinates are **int32 LE in units of 0.001** (100.000 → `0x000186A0`). [E, one
  sample]
- The bytes between the name and the first coordinate (`00 01 80 00 00 00`) and the two
  trailing zero bytes are not decoded yet.
- DISPON prints the values back as `100.000` (three decimals).

## 4. `.COD` (PLC object, kind 5E)

See `corpus/golden/plc/P1.COD` (not decoded yet). PLC.EXE writes `NAME.ERR` even on
success.
