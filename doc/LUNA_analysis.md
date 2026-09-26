# LUNA interpreter — abilities (Sony SRX-611)

**Image:** `ROM1-C.bin` · **OS:** OS+/386 V2.0 · **CPU:** 80486 real mode
**Subsystem:** LUNA robot-programming language (compile → *LUNA Object code* → execute)

LUNA is the robot task language of the SRX controller. Programs are edited on the
teach pendant / PC, compiled to an object code, and executed by the controller.
The evidence for its capabilities comes from the LUNA error strings, the
opcode/keyword table at `0xD99D2`, the command strings of the teach-pendant menus,
and the object-code decode cluster (see `FW\SRX6-CPU\2\c_decomp_luna\`).

---

## 1. Program / execution model

| Concept | Evidence |
|---|---|
| Program stored per task, compiled to object code | `LUNA Object code error` |
| Program memory per task, limited | `LUNA program memory error`, `28k(lun), 32k(plc)` |
| Tasks have a "type" (program category) | `this task's type number was set` |
| Task classes: ROBOT / PLC / SYS / PERI | `PERItask`, `SYStask`, `PLCtask`, `ROBOTtask` |
| Interpreter runs under the controller OS as tasks | OS syscall layer, `task_create`/`task_scheduler` |

The LUNA object-code decode cluster (`token_dispatch` @0xC5CC4 + handlers
`util_C5F6C..util_C631C`, the line formatter family `util_C6A3C..fn_C7C14`) turns
opcodes into mnemonic text — this is what the TP "LIST" view uses.

---

## 2. Instruction set (opcode/keyword table @ `0xD99D2`)

The VM instruction set, in table order:

| Opcode | Meaning (inferred) |
|---|---|
| `END` | end of program |
| `MC`, `MCE` | memory copy / memory copy end |
| `JP(`, `JPE(` | jump / jump-if-equal (conditional branch) |
| `T`, `C`, `N` | single-letter conversions/constants |
| `MOV(` | move / assign |
| `CMP(` | compare |
| `DEC(`, `INC(` | decrement / increment |
| `ADD(`, `SUB(` | add / subtract |
| `CRST(` | counter reset |
| `FILL(` | array/block fill |
| `BGET(`, `BSET(` | bit IO get / set (PLC bits) |
| `CGET(`, `CSET(` | channel IO get / set (PLC channels) |
| `=`, ` ` | assignment / separator |
| `PCCD` | PC-card command |

This is a stack/register-style bytecode with arithmetic, compare, branch, memory
and I/O primitives — the low-level target of the LUNA compiler.

---

## 3. Data types (from TP "type list" / variable menus)

- **INT** variable, **REAL** variable
- **POINT** variable (robot pose, `n(m) point data`)
- **STRING** variable
- **INT array**, **REAL array**
- **DATI** variable (integer IO/data register), **DATR** variable (real IO/data register)
- **UTP** variable — *read from PLC*

Runtime type errors handled: `LUNA Integer error`, `LUNA Parameter error`,
`LUNA Array number error`, `LUNA Point number error`.

---

## 4. Control flow

- **FOR** loops (`LUNA FOR loop error`)
- **CALL / RETURN** with nesting (`LUNA CALL nest error`)
- **BRANCH / labels** (`LUNA Branch error`)
- **INTERRUPT** handling (`LUNA Interrupt error`)
- Conditional jumps `JP(` / `JPE(`

---

## 5. Robot motion

Motion-related commands visible in the TP/point menus (executed via LUNA robot commands,
errors reported as `LUNA Robot command error`, `LUNA Axis{1..4} robot/system/point limit error`):

- **POINT GO** (point-to-point move)
- **POINT CIRCLE GO** (circular interpolation)
- **POINT LINE GO** (linear interpolation)
- **HOME RETURN**
- **POINT CHANGE**, **POINT COPY**
- **SPEED(POINT GO)**, **SPEED(TEACH MOTION)**, **MAX SPEED**, **MOTION SPEED**
- **SERVO ON / OFF**, **BRAKE ON / OFF**
- Coordinate systems `SYSTEM OFFSET`, `SYSTEM LIMIT`, `TOOL`, `PAYLOAD`
- 4 axes (X, Y, Z, R) — SCARA / 4-XYZR / P-XY / P-SCA / EARTH robot kinds

---

## 6. I/O and PLC integration

- Channel IO: `CGET` / `CSET` — errors `PLC CGET channel error`, `PLC CSET channel error`
- Bit IO: `BGET` / `BSET` — `PLC BGET/BSET bit num error`
- Counters: `CRST` — `PLC CRST no def counter error`
- **UTP** variables read values from the PLC
- PLC task runs alongside the robot task (`PLC program code error`, `PLC program memory error`)

---

## 7. Math

- Arithmetic opcodes `ADD`, `SUB`, `INC`, `DEC`, `CMP`
- Floating point via x87 (`fnstcw`/`fistp`/`fld`/`fstp` in the value/format helpers; `format_real` @0x72994)
- `LN` operand and `SQRT` operand errors → natural log and square root functions

---

## 8. Storage

- **PC card (PCMCIA, FAT12)**: program `.OBJ`, point data `.DAT`, PLC program `.COD`,
  keep-relay `.KEE`, controller params `.CTR`, "ALL" — errors `LUNA Memory card error`
- `PCCD` opcode and the SRX-CARD / MSDOS5.0 / FAT12 structures at `0xD9B00`

---

## 9. Safety / conformance

- Safety specs **RIA** and **VDE** (`because of RIA`, `because of VDE`)
- Emergency stop, TP safety line, PC-BOX safety line, carrier line, safety switch
- Robot always stops on limit/torque/position/speed errors

---

## 10. LUNA function set decoded (see `FW\SRX6-CPU\2\c_decomp_luna\`)

| Group | Functions |
|---|---|
| Token dispatch | `token_dispatch` @0xC5CC4 |
| Per-type operand/token formatters | `util_C5F6C, C6014, C60BC, C60FC, C613C, C6194, C61EC, C6244, C62AC, C631C` |
| Formatter helpers | `util_C643C, util_C667C, util_61DBC` |
| Object-code line formatter family | `util_C6A3C … fn_C7C14, fn_C805C, fn_C813C/C816C/C8194/C81BC` |
| Variable / point / motion resolution | `point_var_dispatch` @0x6F7DC, `os_C87FC`, `os_C8FC4` |

Files (grouped by name prefix): `util.c`, `token.c`, `fn.c`, `os.c`, `point.c`.
Each function is emitted as Hex-Rays C with the full original assembly in comments
(objdump style). Five functions use invalid relative jump tables and remain
assembly-only (`fn_C7C14`, `fn_C805C`, `point_var_dispatch`, `util_C667C`);
`token_dispatch` was reconstructed by hand.

---

## 11. Confidence notes

- The **opcode/keyword table** and **error strings** are direct artifacts of the
  firmware and are high-confidence.
- The **instruction meanings** (e.g. `MC`=memory copy) are inferred from naming and
  operand shapes; exact semantics need dynamic tracing.
- The **LUNA function set** was identified from the object-code decode cluster
  (token dispatch + handlers + the family that reads the `0xF1xx` operand/mnemonic
  data and calls `token_dispatch`). It is the language decode/format layer that the
  interpreter and the TP program listing both use.
