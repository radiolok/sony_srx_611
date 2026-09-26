# LUNA / PLC keyword and token map (from SRXWIN + firmware)

**Scope:** the keyword sets of the LUNA robot language and the PLC language, and how they are
coded, as recovered from the host toolchain (`SRXWIN/LUNNA.EXE`, `ANNUL.EXE`, `PLC.EXE`,
`DPLC.EXE`) and cross-checked against the CPU firmware (`FW/SRX6-CPU/2/ROM1-C.bin`).
**Status:** static analysis. Meanings of individual attribute bytes are partly inferred and
are marked as such. The keyword semantics are documented in
[`SRXMONIE_help.md`](SRXMONIE_help.md) ("LUNA language reference", "PLC language reference").
**Reproduce:** `python3 tools/srxwin/lunna_symtab.py SRXWIN/LUNNA.EXE [--md]`.

---

## 1. Key findings

1. **LUNNA.EXE embeds the complete LUNA symbol table.** It is at file offset `0x135E4` and
   holds **230 alphabetically sorted records of 15 bytes**: `name[9]` (NUL-padded) followed by
   6 attribute bytes `d0…d5`.
2. **Token-code rule** (verified against ANNUL's decoder, §3):
   * if `d3 = 0`, then `d2` is the primary token code (e.g. `IF`=`62`, `CALL`=`6A`,
     `DO`=`80`, `MVP`=`92`);
   * if `d3 ≠ 0`, then `d3` is the primary token (a *group*) and `d2` is the sub-index inside it
     (e.g. `SIN` = group `78` sub `00`, `STRTOK` = group `79` sub `19`,
     `TPSTAT` = group `0A` sub `07`).
3. **Correction for AGENTS.md / earlier notes:** the firmware table at `0xD99D2` is the
   **PLC** instruction-mnemonic table, not a LUNA opcode table. Its order is
   `END MC MCE JP( JPE( T C MOV( CMP( DEC( INC( CRST( FILL( ADD( SUB( BGET( BSET( CGET( CSET(`,
   identical to the mnemonic table in `DPLC.EXE` (the PLC decompiler). The `N` that appeared in
   earlier notes is a record-header byte (`0x4E`), not a mnemonic (§4).
4. **The CPU application code is 32-bit.** `token_dispatch` (`0xC5CC4`) reads cleanly only as
   32-bit code (`push ebp; mov ebp,esp; sub esp,14h; mov eax,[ebp+8]…`). It first reads the token
   byte (`mov al,[edi]`) and branches on `al ≥ 80h` and `al ≤ 21h`, which fits the token ranges
   below (operands `00–34h`, statements `62h–E5h`). The IDA database already decodes it as 32-bit,
   but the segment is based at 0, not at the link base `0xFFE00000` (see AGENTS.md §8).

---

## 2. Attribute bytes (d0…d5)

| Byte | Meaning | Confidence |
|---|---|---|
| `d0` | argument count (`FF` = variable / special syntax) | high: `SIN`=1, `ATAN2`=2, `CHGACCP`=6, declarations `FF` |
| `d1` | syntactic class (see the table below) | classes are consistent. The names are my interpretation |
| `d2` | token code, or sub-index when `d3 ≠ 0` | high (cross-checked with ANNUL) |
| `d3` | token group, or `0` | high |
| `d4d5` | 16-bit LE value, the same for all members of a class/group (e.g. all math functions `0096`/`0097`) | probably a parser/code-generator routine index. Unverified |

| `d1` | Members (examples) | Interpretation |
|---|---|---|
| `00` | `INIT EMG ERROR` | task-section labels |
| `01` | `DO RESET SRV EGSTS ERF RSCLR TLRST` | statements without an argument list |
| `03` | `INTR1…INTR5` | interrupt enable |
| `04`/`05`/`09` | `INFLG OUTFLG` / `INPC OUTPC` / `INP OUTP USRI USRO` | I/O operands and functions |
| `06` | `DIST ANGL CHG… GET… STR… TASK HOME RSSET PRIO VGET…` | built-in procedures/functions |
| `08` | `READ WRITE RSINP RSOUT PALLET TRACK INTRPTn MLTIN TPWRITE VEXE` | I/O / multi-argument statements |
| `0A` | `INT REAL POINT STRING EXTRN PUBLIC FNC INTP REALP POINTP INCLUDE STATIC DEF` | declarations |
| `0B` | `IF ELSE ENDIF FOR NEXT WHILE ENDW BREAK CALL RET GO STOP END IF! WHILE! INITEND` | control flow |
| `0C` | math functions, `HOMING…QSTOP`, `MCLOAD…MCCLOSE`, `GETERR RSTERR` | functions |
| `0D` | `OFFSET SHIFT FORM PICTURE` | coordinate statements |
| `0E` | `PFLAG…TRCKCHERR`, `TIME…CPV`, `DATI DATR MCDATI MCDATR` | system/status variables |
| `0F` | `HERE IPDATA HEREP HEREA` | position variables |
| `10` | `AND OR NOT THEN TO ON OF OFF LEFT RIGHT AUTO` | syntax words / operators (code = parser sub-value, not an object token) |
| `81`–`88` | `TRACKON…`, `LINE CIRCLE CIRCLE2`, `PRE MOVCHK`, `SERVO`, `MVX…MVA VEL DLY OVT ACC FOS PFOS PASS…AWAKE`, `ISTOP` | motion statements |
| `8F` | `P P0…P11` | point variables (bit 7 of `d1` is set for motion statements and point variables) |

---

## 3. Primary token space

| Token | Group / statement | Members (sub-index) | ANNUL cross-check |
|---|---|---|---|
| `08` / `09` | `DATI(` / `DATR(` | — | operand switch case 9 prints `DATI(`/`DATR(` ✓ |
| `0A` | status variables | `PFLAG`0 `MVCERR`1 `REACH`2 `ISSTAT`3 `PRSTAT`4 `RSSTAT`5 `RSSTAT2`6 `TPSTAT`7 `FOSMOD`8 `TRCKCHERR`9 | case 10 → switch `@073D5` same order ✓ |
| `0B` | system variables | `TIME`0 `DTIME`1 `PAI`2 `EX1`3 `CPMAX`4 `ACY`5 `CPV`6 | case 11 → switch `@07483` same order ✓ |
| `11` / `12` | `MCDATI` / `MCDATR` | — | case 18 ✓ |
| `20` | `P0`…`P11` | sub = point register | — |
| `21` | `P` (point array) | — | case 33 `P%d(` ✓ |
| `25` | `HERE`0 `IPDATA`1 | | case 37 ✓ |
| `26` / `27` | `HEREP` / `HEREA` | | case 39 ✓ |
| `2C`/`2D` | `INP` / `OUTP` | | cases 44/45 ✓ |
| `2E`/`2F` | `INPC` / `OUTPC` | | case 47 ✓ |
| `30`/`31` | `INFLG` / `OUTFLG` | | case 48 ✓ |
| `32` | `MLTIN` | | |
| `33`/`34` | `USRI` / `USRO` | | cases 51/52 ✓ |
| `4E`/`4F`/`50` | `AND` / `OR` / `NOT` | | |
| `60` | `DEF`; declarations are group `60` (`INT`01 `REAL`02 `POINT`03 `EXTRN`04 `PUBLIC`05 `FNC`06 `STRING`07 `INTP`11 `REALP`12 `POINTP`13 `INCLUDE`16 `STATIC`17) | | |
| `62`–`73` | `IF`62 `ELSE`63 `ENDIF`64 `FOR`65 `NEXT`66 `WHILE`67 `ENDW`68 `BREAK`69 `CALL`6A `RET`6D `GO`6E `STOP`6F `END`70 `IF!`71 `WHILE!`72 `INITEND`73 | | |
| `78` | math functions | `SIN`0 `COS`1 `TAN`2 `ASIN`3 `ACOS`4 `ATAN`5 `ATAN2`6 `EXP`7 `LN`8 `SQRT`9 `ABS`A `FIX`B `SHR`C `SHL`D `DEGRAD`E `RADDEG`F | |
| `79` | built-in functions | `DIST`0 `ANGL`1 `GETARML`2 `CHGARML`3 `GETHOMC`4 `CHGHOMC`5 `CHGACCP`6 `CHGMOTS`7 `GETSOFF`8 `CHGSOFF`9 `GETDATE`A `GETTIME`B `SETPFLAG`C `GETPFLAG`D `STRCHK`E `STRLEN`F `STONUM`10 `NUMTOS`11 `STRSET`12 `STRSRCH`13 `STRGET`14 `STRNGET`15 `STRGETR`16 `STRUPR`17 `STRLWR`18 `STRTOK`19 | switches `@05D8C` (0–C) and `@09203` (D–19) ✓ |
| `7A` | `PALLET`0 `PALLET4`1 `TRACK`2 | | |
| `7B` / `7C` | `INTRPT1…5` (0–4) / `INTR1…5` (0–4) | | |
| `7D`–`7F` | `TLDEF` / `TLSEL` / `TLRST` | | |
| `80` | `DO` | | |
| `81`–`97` | `VEL`81 `DLY`82 `OVT`83 `ACC`84 `PRE`85 `FOS`86 `PFOS`87 `PASSP`88 `LINE`89 `CIRCLE`8A `MOVCHK`8B `SERVO`8D `MVPULS`8E `FOSRST`8F `ISTOP`90 `PASS`91 `MVP`92 `MVA`93 `AWAKE`96 `CIRCLE2`97 | | |
| `94` / `95` | `MVX MVY MVZ MVR` (1–4) / `AMVX…AMVR` (1–4) | | switches `@066D8` / `@06735` ✓ |
| `98` | `TRACKON`0 `TRACKOF`1 `TRCKCHK`2 | | |
| `B0`–`B6` | `OFFSET`B0 `RESET`B2 `SHIFT`B3 `FORM`B4 `CHGFRM`B5 `GETFRM`B6 | | |
| `B7`–`BB` | `READ`/`READ2`, `WRITE`/`WRITE2`, `RSSET`/`RSSET2`, `RSINP`/`RSINP2`, `RSOUT`/`RSOUT2` (sub 0/1) | | |
| `BC`–`C1` | `TPINP`BC `TPWRITE`BD `POUT`BE `PIN`BF `RSSPEED` (C0) `RSCLR` (C1) | | |
| `D0` | `PRIO` | | |
| `D1` | task control | `HOMING`0 `TYPESET`1 `START`2 `CONTINUE`3 `STEP`4 `QSTOP`5 | switch `@06006` ✓ |
| `D2` | memory card | `MCLOAD`0 `MCSAVE`1 `MCOPEN`2 `MCCLOSE`3 | switch `@061AD` ✓ |
| `D3` | `GETERR`0 `RSTERR`1 | | |
| `D4` | system | `GETSM`0 `RELSM`1 `SRV`2 `HOME`3 `TASK`4 `EGSTS`5 `ERF`6 | switch `@063E8` (2–6) ✓ |
| `E0`–`E5` | vision | `PICTURE`E0 `VCMD`E1 `VDAT`E2 `GCALIB`/`SCALIB` (E3, sub 0/1) `VGET`E4 `VEXE`E5 | |

ANNUL addresses are MZ-image offsets. The "operand switch" is ANNUL `@07DD5` (53 cases,
dispatched on the operand-type byte at `DS:7717h`). Its unlisted cases (0–2, 3–8, …) are
numeric/string literals and variable references that print via `%d`/`%s`/`%X` formats.

**Not yet mapped:** how statements are laid out in a `.OBJ` (operand encoding, line numbers,
jump targets). That needs either tracing ANNUL's statement decoder (its keyword emitter
indexes the keyword string pool, so there are no direct string xrefs) or, more cheaply,
compiling small test programs with the original `LUNNA.EXE` under DOSBox-X and diffing the
`.OBJ` output.

---

## 4. PLC instruction mnemonics

| Source | Where | Content |
|---|---|---|
| Firmware | `ROM1-C.bin` `0xD99D2` (right after the E401 message) | variable-length records: 7-byte header `02 xx F1 00 00 len 00` (xx increases per entry. Exact semantics not decoded) + NUL-terminated name |
| DPLC.EXE | decompiler string table | same 19 mnemonics in the same order, followed by `=` |
| PLC.EXE | compiler | bare mnemonics `END MCE JPE MOV CMP INC DEC ADD SUB CRST FILL BGET BSET CGET CSET` plus operand patterns `R##C K##C T### C### I### L###` |

Order: `END MC MCE JP( JPE( T C MOV( CMP( DEC( INC( CRST( FILL( ADD( SUB( BGET( BSET( CGET( CSET(`.
PLC special relays (help file): `ONLINE SCAN ERR EMG FIRST CLK… OVERFLOW ZERO FULL LARGE AUTO`.

---

## 5. Full LUNA symbol table (LUNNA.EXE, sorted by token)

`token` applies the rule from §1. `sub-index` is `d2` when the keyword belongs to a group.
The class names are interpretations (§2).

| Keyword | args (d0) | class (d1) | token | sub-index | d4d5 |
|---|---|---|---|---|---|
| `OF` | 0 | `10` syntax word / operator | `00` | — | `0110` |
| `OFF` | 0 | `10` syntax word / operator | `00` | — | `0110` |
| `THEN` | 0 | `10` syntax word / operator | `00` | — | `010F` |
| `TO` | 0 | `10` syntax word / operator | `00` | — | `0109` |
| `INIT` | 0 | `00` task-section label | `01` | — | `0112` |
| `ON` | 0 | `10` syntax word / operator | `01` | — | `0111` |
| `RIGHT` | 0 | `10` syntax word / operator | `01` | — | `010C` |
| `EMG` | 0 | `00` task-section label | `02` | — | `0112` |
| `LEFT` | 0 | `10` syntax word / operator | `02` | — | `010D` |
| `AUTO` | 0 | `10` syntax word / operator | `03` | — | `010E` |
| `ERROR` | 0 | `00` task-section label | `03` | — | `0112` |
| `DATI` | 0 | `0E` system/status variable | `08` | — | `00CD` |
| `DATR` | 0 | `0E` system/status variable | `09` | — | `00CE` |
| `PFLAG` | 0 | `0E` system/status variable | `0A` | 00 | `00D2` |
| `MVCERR` | 0 | `0E` system/status variable | `0A` | 01 | `00D2` |
| `REACH` | 0 | `0E` system/status variable | `0A` | 02 | `00D2` |
| `ISSTAT` | 0 | `0E` system/status variable | `0A` | 03 | `00D2` |
| `PRSTAT` | 0 | `0E` system/status variable | `0A` | 04 | `00D2` |
| `RSSTAT` | 0 | `0E` system/status variable | `0A` | 05 | `00D2` |
| `RSSTAT2` | 0 | `0E` system/status variable | `0A` | 06 | `00D2` |
| `TPSTAT` | 0 | `0E` system/status variable | `0A` | 07 | `00D2` |
| `FOSMOD` | 0 | `0E` system/status variable | `0A` | 08 | `00D2` |
| `TRCKCHERR` | 0 | `0E` system/status variable | `0A` | 09 | `00D2` |
| `TIME` | 0 | `0E` system/status variable | `0B` | 00 | `00DC` |
| `DTIME` | 0 | `0E` system/status variable | `0B` | 01 | `00DC` |
| `PAI` | 0 | `0E` system/status variable | `0B` | 02 | `00DC` |
| `EX1` | 0 | `0E` system/status variable | `0B` | 03 | `00DC` |
| `CPMAX` | 0 | `0E` system/status variable | `0B` | 04 | `00DC` |
| `ACY` | 0 | `0E` system/status variable | `0B` | 05 | `00DC` |
| `CPV` | 0 | `0E` system/status variable | `0B` | 06 | `00DC` |
| `MCDATI` | 0 | `0E` system/status variable | `11` | — | `00D0` |
| `MCDATR` | 0 | `0E` system/status variable | `12` | — | `00D0` |
| `P0` | 0 | `8F` point variable | `20` | 00 | `00DD` |
| `P1` | 0 | `8F` point variable | `20` | 01 | `00DD` |
| `P2` | 0 | `8F` point variable | `20` | 02 | `00DD` |
| `P3` | 0 | `8F` point variable | `20` | 03 | `00DD` |
| `P4` | 0 | `8F` point variable | `20` | 04 | `00DD` |
| `P5` | 0 | `8F` point variable | `20` | 05 | `00DD` |
| `P6` | 0 | `8F` point variable | `20` | 06 | `00DD` |
| `P7` | 0 | `8F` point variable | `20` | 07 | `00DD` |
| `P8` | 0 | `8F` point variable | `20` | 08 | `00DD` |
| `P9` | 0 | `8F` point variable | `20` | 09 | `00DD` |
| `P10` | 0 | `8F` point variable | `20` | 0A | `00DD` |
| `P11` | 0 | `8F` point variable | `20` | 0B | `00DD` |
| `P` | 0 | `8F` point variable | `21` | — | `00E0` |
| `HERE` | 0 | `0F` position variable | `25` | 00 | `00E6` |
| `IPDATA` | 0 | `0F` position variable | `25` | 01 | `00E6` |
| `HEREP` | 0 | `0F` position variable | `26` | — | `00F0` |
| `HEREA` | 0 | `0F` position variable | `27` | — | `00F0` |
| `INP` | 0 | `09` I/O operand | `2C` | — | `00F5` |
| `INP` | 0 | `09` I/O operand | `2C` | — | `00F5` |
| `OUTP` | 0 | `09` I/O operand | `2D` | — | `00F6` |
| `INPC` | 3 | `05` I/O channel fn | `2E` | — | `00F7` |
| `OUTPC` | 3 | `05` I/O channel fn | `2F` | — | `00F8` |
| `INFLG` | 2 | `04` flag I/O fn | `30` | — | `00F9` |
| `OUTFLG` | 2 | `04` flag I/O fn | `31` | — | `00FA` |
| `MLTIN` | 0 | `08` I/O statement / multi-arg | `32` | — | `00FB` |
| `USRI` | 0 | `09` I/O operand | `33` | — | `00FC` |
| `USRO` | 0 | `09` I/O operand | `34` | — | `00FC` |
| `AND` | 0 | `10` syntax word / operator | `4E` | — | `0032` |
| `OR` | 0 | `10` syntax word / operator | `4F` | — | `003C` |
| `NOT` | 0 | `10` syntax word / operator | `50` | — | `0046` |
| `DEF` | var. | `0A` declaration | `60` | — | `0190` |
| `INT` | var. | `0A` declaration | `60` | 01 | `0190` |
| `REAL` | var. | `0A` declaration | `60` | 02 | `0190` |
| `POINT` | var. | `0A` declaration | `60` | 03 | `0190` |
| `EXTRN` | var. | `0A` declaration | `60` | 04 | `0190` |
| `PUBLIC` | var. | `0A` declaration | `60` | 05 | `0190` |
| `FNC` | var. | `0A` declaration | `60` | 06 | `0190` |
| `STRING` | var. | `0A` declaration | `60` | 07 | `0190` |
| `INTP` | var. | `0A` declaration | `60` | 11 | `012C` |
| `REALP` | var. | `0A` declaration | `60` | 12 | `012C` |
| `POINTP` | var. | `0A` declaration | `60` | 13 | `012C` |
| `INCLUDE` | var. | `0A` declaration | `60` | 16 | `0190` |
| `STATIC` | var. | `0A` declaration | `60` | 17 | `0190` |
| `IF` | 0 | `0B` control flow | `62` | — | `019A` |
| `ELSE` | 0 | `0B` control flow | `63` | — | `019B` |
| `ENDIF` | 0 | `0B` control flow | `64` | — | `019C` |
| `FOR` | 0 | `0B` control flow | `65` | — | `019D` |
| `NEXT` | 0 | `0B` control flow | `66` | — | `019E` |
| `WHILE` | 0 | `0B` control flow | `67` | — | `019F` |
| `ENDW` | 0 | `0B` control flow | `68` | — | `01A0` |
| `BREAK` | 0 | `0B` control flow | `69` | — | `01A1` |
| `CALL` | 0 | `0B` control flow | `6A` | — | `01A2` |
| `RET` | 0 | `0B` control flow | `6D` | — | `01A3` |
| `GO` | 0 | `0B` control flow | `6E` | — | `01A4` |
| `STOP` | 0 | `0B` control flow | `6F` | — | `01A5` |
| `END` | 0 | `0B` control flow | `70` | — | `01A6` |
| `IF!` | 0 | `0B` control flow | `71` | — | `019A` |
| `WHILE!` | 0 | `0B` control flow | `72` | — | `019F` |
| `INITEND` | 0 | `0B` control flow | `73` | — | `01A7` |
| `SIN` | 1 | `0C` function (math/task/card/err) | `78` | 00 | `0096` |
| `COS` | 1 | `0C` function (math/task/card/err) | `78` | 01 | `0096` |
| `TAN` | 1 | `0C` function (math/task/card/err) | `78` | 02 | `0096` |
| `ASIN` | 1 | `0C` function (math/task/card/err) | `78` | 03 | `0096` |
| `ACOS` | 1 | `0C` function (math/task/card/err) | `78` | 04 | `0096` |
| `ATAN` | 1 | `0C` function (math/task/card/err) | `78` | 05 | `0096` |
| `ATAN2` | 2 | `0C` function (math/task/card/err) | `78` | 06 | `0097` |
| `EXP` | 1 | `0C` function (math/task/card/err) | `78` | 07 | `0096` |
| `LN` | 1 | `0C` function (math/task/card/err) | `78` | 08 | `0096` |
| `SQRT` | 1 | `0C` function (math/task/card/err) | `78` | 09 | `0096` |
| `ABS` | 1 | `0C` function (math/task/card/err) | `78` | 0A | `0096` |
| `FIX` | 1 | `0C` function (math/task/card/err) | `78` | 0B | `0096` |
| `SHR` | 2 | `0C` function (math/task/card/err) | `78` | 0C | `0097` |
| `SHL` | 2 | `0C` function (math/task/card/err) | `78` | 0D | `0097` |
| `DEGRAD` | 1 | `0C` function (math/task/card/err) | `78` | 0E | `0096` |
| `RADDEG` | 1 | `0C` function (math/task/card/err) | `78` | 0F | `0096` |
| `DIST` | 2 | `06` built-in procedure/function | `79` | 00 | `0258` |
| `ANGL` | 3 | `06` built-in procedure/function | `79` | 01 | `0259` |
| `GETARML` | 1 | `06` built-in procedure/function | `79` | 02 | `025A` |
| `CHGARML` | 2 | `06` built-in procedure/function | `79` | 03 | `025B` |
| `GETHOMC` | 1 | `06` built-in procedure/function | `79` | 04 | `025C` |
| `CHGHOMC` | 2 | `06` built-in procedure/function | `79` | 05 | `025D` |
| `CHGACCP` | 6 | `06` built-in procedure/function | `79` | 06 | `025E` |
| `CHGMOTS` | 4 | `06` built-in procedure/function | `79` | 07 | `025F` |
| `GETSOFF` | 5 | `06` built-in procedure/function | `79` | 08 | `0260` |
| `CHGSOFF` | 5 | `06` built-in procedure/function | `79` | 09 | `0261` |
| `GETDATE` | 3 | `06` built-in procedure/function | `79` | 0A | `0262` |
| `GETTIME` | 3 | `06` built-in procedure/function | `79` | 0B | `0263` |
| `SETPFLAG` | 2 | `06` built-in procedure/function | `79` | 0C | `0264` |
| `GETPFLAG` | 1 | `06` built-in procedure/function | `79` | 0D | `0265` |
| `STRCHK` | 2 | `06` built-in procedure/function | `79` | 0E | `0266` |
| `STRLEN` | 1 | `06` built-in procedure/function | `79` | 0F | `0267` |
| `STONUM` | 1 | `06` built-in procedure/function | `79` | 10 | `0267` |
| `NUMTOS` | 1 | `06` built-in procedure/function | `79` | 11 | `0268` |
| `STRSET` | 3 | `06` built-in procedure/function | `79` | 12 | `0269` |
| `STRSRCH` | 2 | `06` built-in procedure/function | `79` | 13 | `026A` |
| `STRGET` | 2 | `06` built-in procedure/function | `79` | 14 | `0266` |
| `STRNGET` | 3 | `06` built-in procedure/function | `79` | 15 | `026B` |
| `STRGETR` | 2 | `06` built-in procedure/function | `79` | 16 | `0266` |
| `STRUPR` | 1 | `06` built-in procedure/function | `79` | 17 | `0267` |
| `STRLWR` | 1 | `06` built-in procedure/function | `79` | 18 | `0267` |
| `STRTOK` | 3 | `06` built-in procedure/function | `79` | 19 | `0269` |
| `PALLET` | 7 | `08` I/O statement / multi-arg | `7A` | 00 | `02BD` |
| `PALLET4` | 8 | `08` I/O statement / multi-arg | `7A` | 01 | `02BD` |
| `TRACK` | 8 | `08` I/O statement / multi-arg | `7A` | 02 | `02BE` |
| `INTRPT1` | 2 | `08` I/O statement / multi-arg | `7B` | 00 | `0320` |
| `INTRPT2` | 2 | `08` I/O statement / multi-arg | `7B` | 01 | `0320` |
| `INTRPT3` | 2 | `08` I/O statement / multi-arg | `7B` | 02 | `0320` |
| `INTRPT4` | 2 | `08` I/O statement / multi-arg | `7B` | 03 | `0320` |
| `INTRPT5` | 2 | `08` I/O statement / multi-arg | `7B` | 04 | `0320` |
| `INTR1` | 1 | `03` interrupt INTRn | `7C` | 00 | `0321` |
| `INTR2` | 1 | `03` interrupt INTRn | `7C` | 01 | `0321` |
| `INTR3` | 1 | `03` interrupt INTRn | `7C` | 02 | `0321` |
| `INTR4` | 1 | `03` interrupt INTRn | `7C` | 03 | `0321` |
| `INTR5` | 1 | `03` interrupt INTRn | `7C` | 04 | `0321` |
| `TLDEF` | 4 | `06` built-in procedure/function | `7D` | — | `0384` |
| `TLSEL` | 1 | `06` built-in procedure/function | `7E` | — | `0384` |
| `TLRST` | 0 | `01` statement (no-arg / DO) | `7F` | — | `0385` |
| `DO` | 0 | `01` statement (no-arg / DO) | `80` | — | `01F4` |
| `VEL` | 1 | `86` motion statement | `81` | — | `01F5` |
| `DLY` | 1 | `86` motion statement | `82` | — | `01F6` |
| `OVT` | 1 | `86` motion statement | `83` | — | `01F7` |
| `ACC` | 1 | `86` motion statement | `84` | — | `01F8` |
| `PRE` | 1 | `83` motion check | `85` | — | `0207` |
| `FOS` | 1 | `86` motion statement | `86` | — | `01FB` |
| `PFOS` | 1 | `86` motion statement | `87` | — | `01FB` |
| `PASSP` | 1 | `86` motion statement | `88` | — | `01FC` |
| `LINE` | 0 | `82` interpolation motion | `89` | — | `01FD` |
| `CIRCLE` | 0 | `82` interpolation motion | `8A` | — | `01FE` |
| `MOVCHK` | 1 | `83` motion check | `8B` | — | `01FF` |
| `SERVO` | 2 | `84` servo | `8D` | — | `0201` |
| `MVPULS` | 1 | `86` motion statement | `8E` | — | `0208` |
| `FOSRST` | 0 | `81` tracking/FOS statement | `8F` | — | `01FA` |
| `ISTOP` | 1 | `88` stop | `90` | — | `0202` |
| `PASS` | 2 | `86` motion statement | `91` | — | `0203` |
| `MVP` | 2 | `86` motion statement | `92` | — | `0205` |
| `MVA` | 2 | `86` motion statement | `93` | — | `0205` |
| `MVX` | 1 | `86` motion statement | `94` | 01 | `01F9` |
| `MVY` | 1 | `86` motion statement | `94` | 02 | `01F9` |
| `MVZ` | 1 | `86` motion statement | `94` | 03 | `01F9` |
| `MVR` | 1 | `86` motion statement | `94` | 04 | `01F9` |
| `AMVX` | 1 | `86` motion statement | `95` | 01 | `0204` |
| `AMVY` | 1 | `86` motion statement | `95` | 02 | `0204` |
| `AMVZ` | 1 | `86` motion statement | `95` | 03 | `0204` |
| `AMVR` | 1 | `86` motion statement | `95` | 04 | `0204` |
| `AWAKE` | 1 | `86` motion statement | `96` | — | `0206` |
| `CIRCLE2` | 0 | `82` interpolation motion | `97` | — | `01FE` |
| `TRACKON` | 0 | `81` tracking/FOS statement | `98` | 00 | `02BF` |
| `TRACKOF` | 0 | `81` tracking/FOS statement | `98` | 01 | `02BF` |
| `TRCKCHK` | 0 | `81` tracking/FOS statement | `98` | 02 | `02BF` |
| `OFFSET` | 5 | `0D` coordinate statement | `B0` | — | `0209` |
| `RESET` | 0 | `01` statement (no-arg / DO) | `B2` | — | `020B` |
| `SHIFT` | 4 | `0D` coordinate statement | `B3` | — | `020C` |
| `FORM` | 1 | `0D` coordinate statement | `B4` | — | `020D` |
| `CHGFRM` | 1 | `06` built-in procedure/function | `B5` | — | `020E` |
| `GETFRM` | 1 | `06` built-in procedure/function | `B6` | — | `020F` |
| `READ` | var. | `08` I/O statement / multi-arg | `B7` | 00 | `0210` |
| `READ2` | var. | `08` I/O statement / multi-arg | `B7` | 01 | `0210` |
| `WRITE` | var. | `08` I/O statement / multi-arg | `B8` | 00 | `0211` |
| `WRITE2` | var. | `08` I/O statement / multi-arg | `B8` | 01 | `0211` |
| `RSSET` | 1 | `06` built-in procedure/function | `B9` | 00 | `0212` |
| `RSSET2` | 1 | `06` built-in procedure/function | `B9` | 01 | `0212` |
| `RSINP` | var. | `08` I/O statement / multi-arg | `BA` | 00 | `0213` |
| `RSINP2` | var. | `08` I/O statement / multi-arg | `BA` | 01 | `0213` |
| `RSOUT` | var. | `08` I/O statement / multi-arg | `BB` | 00 | `0214` |
| `RSOUT2` | var. | `08` I/O statement / multi-arg | `BB` | 01 | `0214` |
| `TPINP` | 1 | `06` built-in procedure/function | `BC` | — | `0215` |
| `TPWRITE` | var. | `08` I/O statement / multi-arg | `BD` | — | `0216` |
| `POUT` | 2 | `06` built-in procedure/function | `BE` | — | `0217` |
| `PIN` | 2 | `06` built-in procedure/function | `BF` | — | `0217` |
| `RSSPEED` | 1 | `06` built-in procedure/function | `C0` | 00 | `0218` |
| `RSCLR` | 0 | `01` statement (no-arg / DO) | `C1` | 00 | `0219` |
| `PRIO` | 1 | `06` built-in procedure/function | `D0` | — | `015E` |
| `HOMING` | 1 | `0C` function (math/task/card/err) | `D1` | 00 | `015F` |
| `TYPESET` | 2 | `0C` function (math/task/card/err) | `D1` | 01 | `0160` |
| `START` | 1 | `0C` function (math/task/card/err) | `D1` | 02 | `015F` |
| `CONTINUE` | 1 | `0C` function (math/task/card/err) | `D1` | 03 | `015F` |
| `STEP` | 1 | `0C` function (math/task/card/err) | `D1` | 04 | `015F` |
| `QSTOP` | 1 | `0C` function (math/task/card/err) | `D1` | 05 | `015F` |
| `MCLOAD` | 2 | `0C` function (math/task/card/err) | `D2` | 00 | `0166` |
| `MCSAVE` | 1 | `0C` function (math/task/card/err) | `D2` | 01 | `0164` |
| `MCOPEN` | 1 | `0C` function (math/task/card/err) | `D2` | 02 | `0165` |
| `MCCLOSE` | 1 | `0C` function (math/task/card/err) | `D2` | 03 | `0165` |
| `GETERR` | 3 | `0C` function (math/task/card/err) | `D3` | 00 | `0161` |
| `RSTERR` | 0 | `0C` function (math/task/card/err) | `D3` | 01 | `0162` |
| `GETSM` | 1 | `06` built-in procedure/function | `D4` | 00 | `0163` |
| `RELSM` | 1 | `06` built-in procedure/function | `D4` | 01 | `0163` |
| `SRV` | 0 | `01` statement (no-arg / DO) | `D4` | 02 | `0162` |
| `HOME` | 1 | `06` built-in procedure/function | `D4` | 03 | `015F` |
| `TASK` | 1 | `06` built-in procedure/function | `D4` | 04 | `015F` |
| `EGSTS` | 0 | `01` statement (no-arg / DO) | `D4` | 05 | `0162` |
| `ERF` | 0 | `01` statement (no-arg / DO) | `D4` | 06 | `0162` |
| `PICTURE` | 1 | `0D` coordinate statement | `E0` | — | `0140` |
| `VCMD` | 5 | `06` built-in procedure/function | `E1` | — | `0140` |
| `VDAT` | 17 | `06` built-in procedure/function | `E2` | — | `0140` |
| `GCALIB` | 5 | `06` built-in procedure/function | `E3` | 00 | `0141` |
| `SCALIB` | 5 | `06` built-in procedure/function | `E3` | 01 | `0141` |
| `VGET` | 2 | `06` built-in procedure/function | `E4` | — | `0140` |
| `VEXE` | var. | `08` I/O statement / multi-arg | `E5` | — | `0140` |
