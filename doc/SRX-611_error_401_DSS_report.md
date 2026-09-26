# SRX-611 — Error Reporting & Error 401 ("Drive Safety Switch" / DSS) Analysis

**Firmware:** `ROM1-C.bin` (1 MB) / IDA DB `ROM1-C.bin.i64`
**Reference manual:** `Sony+SRX+Scara+robot.pdf` (Error Code Guide, section "Error Code Lists")
**Scope:** how errors reach the teach pendant, the full error list, and the exact
generation path of error **401** ("drive safety switch error").

---

## 1. TL;DR

- The teach-pendant error codes are the **`E nnn` numbers** in the *Error Code Guide*
  of the operation manual. The TP firmware (`IC6_M27C256B@DIP28.BIN`, 32 KB) contains
  **no** error text, so the **main CPU** formats `E nnn : <message>` and sends it to the
  pendant (or sends the numeric code that the CPU later resolves).
- The message strings live in a **bilingual (Japanese + English) table** in the main
  firmware at `0xD7E73 … 0xD99C7`. Error **401** resolves to the last-but-one entry:

  | Code | Address (EN) | English text | Japanese text |
  |---|---|---|---|
  | **E400** | `0xD99A3` | `SPD over speed error` | `SPD ｵｰﾊﾞｰｽﾋﾟｰﾄﾞ ｴﾗｰ` |
  | **E401** | `0xD99C7` | **`DSS off error`** | `DSS ｵﾌ ｴﾗｰ` |

- **`DSS` = "Drive Safety Switch"** — a *SMART-option* safety input. So error 401
  = **"Drive Safety Switch off"**. It is generated when the DSS input is OFF while a
  servo-ON is requested.
- **401 is absent from the manual** because the manual's list ends at E400 (`SPD over
  speed error`); E401 is a SMART-option / later-firmware addition (see §5).

---

## 2. The error message table in the firmware

The error messages are stored as consecutive pairs of NUL-terminated strings
(half-width-katakana Japanese, then ASCII English), starting right after the CPU
exception strings:

```
0xD7E73  "0 ﾜﾘｻﾞﾝ ｴﾗｰ" 0xD7E81 "Divide error"            -> E000
0xD7E97  ...             0xD7EA5 "Debug exception"         -> E001
...
0xD998B  "SPD ... ｴﾗｰ"  0xD99A3 "SPD over speed error"    -> E400
0xD99BB  "DSS ｵﾌ ｴﾗｰ"  0xD99C7 "DSS off error"           -> E401
0xD99D2  (LUNA opcode/keyword table starts: END, MC, MCE, JP( ...)
```

The table is indexed **by error code**, not by a 1:1 sequence — the codes have gaps
(matching the gaps in the manual, e.g. E008 → E010 skips the hardware IRQ vector 9,
E014 → E016 skips vector 15, E031 → E100, E382 → E400 …). The code→text lookup is done
through the OS error task (syscall `0x27`, see §4), not by direct string xrefs — which
is why `XrefsTo` on the strings is empty (documented AGENTS.md gotcha #1).

---

## 3. Complete error code list (manual + firmware reconciliation)

Codes marked ✅ are stated in the operation manual. Codes marked *(fw)* exist in
`ROM1-C.bin` but are **not** in the manual (later firmware / SMART additions). Codes in
parentheses are inferred from the firmware message order filling the manual's gaps.

### 3.1 System errors

| Code | Message |
|---|---|
| ✅ E000 | Divide error |
| ✅ E001 | Debug exception |
| ✅ E002 | NMI Debug interruption |
| ✅ E003 | One byte interruption |
| ✅ E004 | Interrupt on overflow |
| ✅ E005 | Array bounds check |
| ✅ E006 | Invalid OP-CODE |
| ✅ E007 | FPU device not available |
| ✅ E008 | Double fault |
| ✅ E010 | Invalid TSS |
| ✅ E011 | Segment not present |
| ✅ E012 | Stack fault |
| ✅ E013 | General protection fault |
| ✅ E014 | Page fault |
| ✅ E016 | Coprocessor error |
| ✅ E030 | System error |
| ✅ E031 | System memory error |
| *(fw)* (E032) | LUNA program memory error |
| *(fw)* (E033) | PLC program memory error |
| *(fw)* (E034) | C/R parameter error |
| ✅ E100 | System task execution error |

### 3.2 LUNA program errors

| Code | Message |
|---|---|
| ✅ E110 | Object code error |
| ✅ E111 | System command error |
| ✅ E112 | Robot command error |
| ✅ E113 | I/O number error |
| ✅ E114 | Point data error |
| ✅ E115 | Point number error |
| ✅ E116 | Parameter error |
| ✅ E117 | Array number error |
| ✅ E118 | Integer error |
| ✅ E119 | FOR loop error |
| ✅ E120 | CALL nest error |
| ✅ E121 | Branch error |
| ✅ E122 | Interrupt error |
| ✅ E123 | LN operand error |
| ✅ E124 | SQRT operand error |
| *(fw)* (E125) | Memory card error |
| *(fw)* (E126) | Not available function |
| ✅ E130–E133 | Axis 1–4 robot limit error |
| ✅ E134–E137 | Axis 1–4 system limit error |
| ✅ E138–E141 | Axis 1–4 point limit error |
| *(fw)* (E142) | CP Motion Error |
| *(fw)* (E143) | Circle Point Error |

### 3.3 PLC program errors

| Code | Message |
|---|---|
| ✅ E200 | PLC program code error |
| ✅ E201 | PLC CGET channel error |
| ✅ E202 | PLC CSET channel error |
| ✅ E203 | PLC BGET bit num error |
| ✅ E204 | PLC BSET bit num error |
| *(fw)* (E205) | PLC CRST no def counter error |

### 3.4 Robot control / servo / AMP / ABE errors

| Code | Message |
|---|---|
| ✅ E300 | Emergency stop error |
| ✅ E301–E304 | Axis 1–4 limit sensor error |
| ✅ E305 | Barrier switch error |
| ✅ E306 | TP safety switch error |
| ✅ E307 | PC safety switch error |
| ✅ E310–E313 | SERVO Axis 1–4 torque limit error |
| ✅ E314–E317 | SERVO Axis 1–4 position error |
| ✅ E318 | SERVO CPU Communication error |
| ✅ E319 | SERVO program error |
| ✅ E320–E323 | AMP Axis 1–4 current error |
| ✅ E324–E327 | AMP Axis 1–4 speed error |
| ✅ E328–E331 | AMP Axis 1–4 rated current error |
| ✅ E332–E335 | AMP Axis 1–4 encoder break error |
| ✅ E336–E339 | AMP Axis 1–4 IPM error |
| ✅ E340 | AMP WDT error |
| ✅ E341 | AMP Ready error |
| ✅ E342 | AMP Main power error |
| *(fw)* (E343) | AMP Main power OV error |
| *(fw)* (E344) | AMP Main power OL error |
| *(fw)* (E345) | AMP regenerative resistor error (回生抵抗) |
| ✅ E350–E353 | ABE Axis 1–4 encoder thermal error |
| ✅ E354–E357 | ABE Axis 1–4 encoder backup error |
| ✅ E358–E361 | ABE Axis 1–4 encoder power error |
| *(fw)* (E362–E365) | ABE Axis 1–4 encoder copy error |
| *(fw)* (E366–E369) | ABE Axis 1–4 homing limit error |
| *(fw)* (E370–E373) | SERVO Axis 1–4 speed detect error |
| ✅ E380 | SERVO CPU WDT error |
| ✅ E381 | SERVO trap error |
| ✅ E382 | SERVO P/S interface error |
| *(fw)* (E383–E386) | SERVO Axis 1–4 servo ON error |
| *(fw)* (E387–E390) | SERVO Axis 1–4 servo OFF error |
| ✅ **E400** | **SPD over speed error** |
| *(fw)* **E401** | **DSS off error  ← drive safety switch** |

---

## 4. How an error is reported to the pendant

The reporting chain is generic; error 401 rides the same path:

```
app_3BD28 (servo-ON request handler)          @0x3BD28
   └─ sys_req_27h(channel, subcode=0, code=0x191)   @0xBE214
        └─ os_syscall_90h_27h()                    @0xCE11D   (EAX=0x27, int 90h)
             └─ OS+/386 syscall 0x27 → error/event task → formats "E nnn : <msg>"
                  └─ sent to teach pendant
```

`sys_req_27h` (decompiled):

```c
__int16 sys_req_27h(char a1, __int16 a2, unsigned __int16 a3) {
  if ( a3 < 0x64u )            // code < 100 → flag it
    *(&loc_75D6 + 2) = 1;
  if ( os_syscall_90h_27h() )  // int 90h, function 0x27
    return 30;
  return 0;
}
```

`os_syscall_90h_27h` loads `EAX = 0x27` and executes `int 90h` (the OS+/386 syscall
trap), passing the error request block.

---

## 5. Error 401 — "Drive Safety Switch" (DSS) off

### 5.1 What "DSS" is (from the operation manual)

From *Safety Instruction → 5. SMART specifications* and the I/O connector tables:

- **DSS = Drive Safety Switch**, present **only on the SMART robot option**.
- It is wired on the **Safety connector**: **DSS0 (pin 12)** and **DSS1 (pin 13)**.
  These two lines **shut the servo down directly in hardware**.
- A third, software-facing copy of the signal is a **System Input** (`DSS`, used by the
  system task; the manual lists it among SI1–SI8) and reaches the CPU as an input bit.
- There is also a **SPD PANEL BOARD** with a *"Hardware Over Speed Detector Circuit"* —
  this is the origin of the adjacent **E400 "SPD over speed error"**.
- The manual's safety-circuit chapter: *"…melting of the contacts of the following
  relays is detected: … the barrier switches (BARSW0/1) and the **drive safety switch
  (DSS0-1, used in SMART only)**. If one contact … melts, SERVO ON will not be
  possible."*

So the "drive safety switch error" **is** `DSS off error` — the controller saw the
Drive Safety Switch in the OFF state when it should have been ON.

### 5.2 Where it is generated (firmware)

`app_3BD28` (`0x3BD28`, pop_rank 126/1298) is the **servo-ON request handler**
(arg = channel 1…8). Its decompilation:

```c
__int16 app_3BD28(unsigned __int8 a1) {
  if (!a1 || a1 > 8u)                 return 16512;      // 0x4080
  if (*(_BYTE *)(&loc_74C4 + a1 + 7) != 1) return 16512;
  v2 = *(_DWORD *)((char *)&loc_74A7 + 4*a1 + 1);
  if (!*(_BYTE *)(v2 + 4))            return 16520;      // 0x4088
  if ((unsigned __int16)*(_DWORD *)v2) return 0;
  motion_3BF20(a1, &v7);
  if ((v7 & 0x81) && motion_BE2B4()) { … }                // servo ON/OFF state machine
  else {
    plc_10334(&v4);                                        // v4 = (0x6228 & 0x10)!=0
    if (v4 != 1 || (app_10C5C(7, &v5), v5)) {
      … os_syscall_90h_50h(…) ;                            // normal servo-on
      return 0;
    } else {
      sys_req_27h(a1, 0, 0x191u);                          // 0x191 = 401  ← ERROR
      return 0;
    }
  }
}
```

The DSS check is the final `else`:

1. `plc_10334(&v4)` → `v4 = (loc_6228 & 0x10) != 0` — an enable/run condition bit.
2. `app_10C5C(7, &v5)` → reads **input index 7** = bit 6 of the input-image byte
   `loc_62B8` (`test byte ptr ds:loc_62B8, 0x40`). This bit is the **DSS input**.
3. If `v4 == 1` **and** `v5 == 0` (DSS input **OFF**) → `sys_req_27h(a1, 0, 0x191)`.

`0x191` = **401** appears **only once** in the whole 1 MB image (at `0x3BE1B`), which
confirms this is the sole source of error 401.

### 5.3 Supporting facts

- `loc_62B8` (`0x62B8`) is the first word of the **system-input image array**
  (`loc_62B8[edi*2]`), refreshed by the I/O scan at `0x109F1` / `0x10B00` from the
  per-board input pointers in `os_6238`.
- `app_10C5C(n)` is the generic "read system-input bit n" helper (bit `(n-1)&7` of
  byte `0x62B8`). `app_3BD28` hardcodes `n=7`.
- `app_3BD28` is called from the main task and motion/point paths:
  `0x1637F, 0x16468, 0x2944F, 0x297CF, 0x473A0, 0x475A0, 0x479A0, 0x5467D, 0x640FA,
  0x641EF, 0xAC2A2, 0xAC33F, 0xAC527`.

---

## 6. Why 401 is not in the operation manual

1. **The manual's `Error Code Lists` end at E400** (`SPD over speed error`). There is
   literally no E401 entry to find — a `401` search only hits the robot model string
   `SRX-611 (L4015)`.
2. **DSS is a SMART-only option.** The manual documents the *standard* robot; the SMART
   safety function (and its dedicated errors) are a separate option. E400 (`SPD over
   speed`) and E401 (`DSS off`) are a pair tied to the SMART safety hardware
   (SPD PANEL BOARD over-speed detector + DSS switch).
3. The firmware is **newer** than the manual: it also contains messages absent from the
   manual — `SERVO … speed detect` (×4), `SERVO … servo ON/OFF` (×8), `ABE … encoder
   copy` (×4), `ABE … homing limit` (×4), `CP Motion`, `Circle Point`, `AMP main power
   OV/OL`, etc. These fill the manual's gaps (E343–E345, E362–E373, E383–E390, E401).

---

## 7. Key addresses (annotated)

| Addr | Name | Role |
|---|---|---|
| `0xD7E73` / `0xD7E81` | error table start | Japanese / English of "Divide error" (E000) |
| `0xD998B` / `0xD99A3` | `SPD over speed error` | **E400** |
| `0xD99BB` / `0xD99C7` | **`DSS off error`** | **E401 (drive safety switch)** |
| `0x3BD28` | `app_3BD28` | servo-ON request handler — **raises 401** |
| `0x3BE1B` | — | `mov [esp+…], 191h` (the only 401 constant) |
| `0x10334` | `plc_10334` | returns `(0x6228 & 0x10) != 0` |
| `0x10C5C` | `app_10C5C` | read system-input bit n (DSS = bit 6 of `0x62B8`) |
| `0x62B8` | `loc_62B8` | system-input image (word array) |
| `0xBE214` | `sys_req_27h` | builds error request (channel, subcode, code) |
| `0x109F1` / `0x10B00` | I/O input scan | populates `loc_62B8` from `os_6238` pointers |
| `0xCE11D` | `os_syscall_90h_27h` | `EAX=0x27`, `int 90h` |

---

## 8. Bottom line

**Error 401 "drive safety switch error" = `DSS off error` (Drive Safety Switch OFF).**
It is raised by `app_3BD28` (`0x3BD28`) when a servo-ON is requested while the SMART
**DSS input (system-input bit 6 of `0x62B8`) is OFF**, and it is dispatched to the
pendant as numeric code `0x191` via `sys_req_27h → os_syscall_90h_27h (int 90h)`.
