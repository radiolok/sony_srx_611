# SRX-C61 controller — hardware overview

Structure of the SRX-C61 controller (the box that drives the SRX-611 arm), put together from
board photos (2026-10-29), the owner's notes on how the boards sit in the chassis, and what
the firmware analysis has shown so far.

How sure each statement is:

- **[P]** read directly off the board photo (part number, silkscreen, connector);
- **[F]** confirmed by firmware analysis (CPU `ROM1-C.bin`, servo `ROM_SERVO.bin`,
  Control board DSP code — see `doc/control_board_firmware.md`);
- **[O]** stated by the owner after inspecting the unit;
- **[H]** hypothesis — still to be checked (continuity test, scope, or firmware).

The owner has **two controller units**. They differ in the CPU board: in one, the i486 sits
in a socket and the SRX6-SIO2 serial mezzanine is fitted on top; in the other, the CPU is
soldered under a heatsink (photo labelled "SRX-CPU 2").

---

## 1. Whole controller

![Controller with the top cover removed](../img/hw/chassis_top.jpg)

*Top view, front of the unit at the bottom. Top left: card cage (CPU + SIO2 mezzanine, two
I/O boards, SERVO). Centre: four motor drivers and, below them, the Control board. Right:
contactors under the black cover. Front edge: the L-shaped SPD panel board, the sealed
lead-acid back-up batteries and their small charger board.* [O][P]

```mermaid
flowchart TB
    subgraph EXT["Outside the box"]
        TP["Teach pendant"]
        PC["PC (SRXWIN)"]
        U232["User RS-232C"]
        SIOP["4 extra ports<br/>RS-232 / RS-485"]
        IO24["24 V field I/O"]
        ARM["Arm: 4 motors X/Y/Z/R<br/>+ absolute encoders"]
        MAINS["AC 200–240 V"]
    end

    subgraph CAGE["Card cage"]
        CPU["SRX6-CPU<br/>i486DX2, pSOS+/386"]
        SIO["SRX6-SIO2 mezzanine<br/>4× 16550"]
        MB["Mother board 1-658-655-21<br/>CPU connector + 5 slots<br/>(5 DPRAM windows)"]
        IOA["SRX6-I/O #1"]
        IOB["SRX6-I/O #2"]
        SRV["SRX6-SERVO<br/>NEC V810"]
    end

    subgraph DRV["Drive section (one long backplane)"]
        CB["Control board 1-659-417-12<br/>2× ADSP-2115"]
        D1["Driver X"]
        D2["Driver Y"]
        D3["Driver Z"]
        D4["Driver R"]
    end

    SPD["SPD panel board 1-661-736-13<br/>over-speed + safety relays"]
    K["Contactors"]
    BAT["Back-up batteries<br/>+ charger"]

    TP & PC & U232 --- CPU
    SIOP --- SIO
    SIO --- CPU
    CPU --- MB
    MB --- IOA & IOB & SRV
    IO24 --- IOA & IOB
    SRV -- "50-pin cable [H]" --- CB
    CB --- D1 & D2 & D3 & D4
    D1 & D2 & D3 & D4 --> ARM
    ARM -- "encoder feedback" --> CB
    MB --- SPD
    SPD --> K
    MAINS --> K --> DRV
    BAT --- MB
```

Key points:

- **Card cage.** CPU board (with the SIO2 mezzanine on one unit), two SRX6-I/O boards and
  **one** SRX6-SERVO board, all on the Mother board. [O] The CPU firmware polls **five slot
  windows** (`0x700000 + n·0x10000`) and classifies boards by a kind byte (1 = servo,
  3 = I/O). [F] The Mother board has one CPU connector and five identical slot connectors
  [P], so 3 of the 5 windows are used here: one servo (kind 1) and two I/O (kind 3). Which
  physical slot maps to which window is still to be confirmed. [H]
- **One SERVO board drives all four axes.** So the CPU's SLOT/AXIS setting must map axes
  1–4 to sub-axes of a single servo slot. [O][H]
- **Drive section.** The four driver modules and the **single** Control board plug into
  one long backplane. Motor power comes into this backplane, and the encoder/feedback
  connector is on it. The feedback signals reach the Control board's connector. [O]
  The firmware on both sides suggests they **end there**: the DSPs read the serial
  absolute encoders over SPORT0 when SERVO sends `0x8082/0x8084` (its `ABSCOPY`
  command), and the incremental counts are probably in the CXD8501R
  (`doc/servo_dsp_link.md` §6). [I][H]
- **Control board** has two ADSP-2115 DSPs; each runs the current loop and the 3-phase
  PWM for **two axes**. [F]
- **SPD panel board** (front, L-shaped) carries the over-speed detector and the safety
  relays that drive the contactors, plus the front-panel connectors. [P][H]

---

## 2. SRX6-CPU — main CPU board (1-676-745-11)

![SRX6-CPU board, unit 2 (CPU soldered under the heatsink)](../img/hw/cpu_board.jpg)

```mermaid
flowchart LR
    CPU486["i486DX2<br/>(socket on unit 1,<br/>soldered + heatsink on unit 2)"]
    GLUE["Altera EPLD<br/>(under pSOS+ licence label)<br/>address decode"]
    SRAM["4× TC551001CF-70L<br/>128K×8 SRAM = 512 KB"]
    FLASH["2× MT28F400B5 (U24/U25)<br/>main firmware 1 MB"]
    BOOT["M27C256B boot EPROM<br/>(DIP socket U23)"]
    USART["3× OKI M82C51A-2<br/>ch1 TP, ch2 PC, ch3 user"]
    PIT["OKI M82C54-2 timer"]
    PIC["2× OKI M82C59A-2 PIC"]
    RS232["RS-232 drivers<br/>(ADM202 etc.)"]
    MEZ["Mezzanine connectors<br/>(top edge) → SRX6-SIO2"]
    BP["Edge connectors TX15-100P + 40P<br/>→ Mother board"]

    CPU486 --- GLUE
    GLUE --- SRAM & FLASH & BOOT & USART & PIT & PIC
    USART --- RS232
    CPU486 --- MEZ
    GLUE --- BP
```

| Item | What | Source |
|---|---|---|
| CPU | Intel i486DX2 (50 MHz internal), flat 32-bit protected mode | [P][F] |
| RAM | 4× Toshiba TC551001CF-70L (128K×8) = 512 KB | [P] |
| Main firmware | 2× MT28F400B5 (U24, U25) → `ROM1-C.bin` 1 MB | [F] |
| Boot | M27C256B in a DIP socket (empty on the photo: removed for dumping) | [P][F] |
| Serial | 3× OKI M82C51A-2 (TP / PC / user RS-232C) | [P][F] |
| Timer, IRQ | OKI M82C54-2, 2× OKI M82C59A-2 | [P][F] |
| Glue logic | Altera PLD (part number hidden under the pSOS+ licence label "SN 062664A") | [P] |
| Other | 50 MHz oscillator, RESET and SELF-CHECK switches, back-up cell for the RTC, DB9 on the bracket | [P][H] |
| **Parameter EEPROM** | **U26 Hitachi HN58V66AFP-10** (8K×8, SOP28, 2.7–5.5 V, date 9644), next to the supercap; holds the `.CTR` block (architecture report §8.7). Not dumped yet (photo 2026-11-08) | [P][F] |
| Refs (photo 2026-11-08) | boot EPROM ST M27C256B-10F1 in socket **U23**; flash 2× 28F400B5-6TE (U24, U25; matches the `MT28F400B5` dumps in `FW/SRX6-CPU/2/`); SRAM 4× TC551001CF-70L (U31, U32, U33, U34); one Altera PLD labelled **CPU99A** under the pSOS+ label; OKI M82C54-2 U30, M82C59A-2 U28/U29, M82C51A-2 U37/U40/U43; Y1 SG51PH 50.0000 MHz; CPU soldered (QFP) under a clip-on heatsink; ADM202 U38; 2×5 pin header on the left edge (PLD JTAG?) | [P][H] |

Memory and I/O maps are in `doc/SRX-611_firmware_architecture.md`.

### 2.1 Unit 1 board — SRX6-CPU 1-658-652-11 (socketed CPU), photo 2026-11-08

![SRX6-CPU 1-658-652-11, unit 1, SIO2 mezzanine removed](../img/hw/cpu_board_unit1.jpg)

This is the earlier PCB revision, from the unit with the socketed i486. The mezzanine connectors along
the top edge are empty in the photo because the SIO2 board has been removed. Board serial: `501438`.
The boot EPROM socket is **U26**, which matches the dump `FW/SRX6-CPU/1/U26_M27C256B@DIP28.BIN`.
This is controller **C61-1039**, the one matched at the factory with the owner's only arm, robot
82790 (rear plates: `doc/robot_parameters.md`).

| Ref | Part (photo) | Role | Source |
|---|---|---|---|
| socket (lower right) | i486 in a PGA socket under a clip-on heatsink; pSOS+ licence label "Integrated Systems SN 061321A" on the socket | CPU | [P] |
| Y1 | Epson SG51PH 50.0000 MHz | CPU clock oscillator | [P] |
| U22, U23 | 2× Altera EPM7064SLC84-10, labels **CPU01E** (U22) and **CPU02B** (U23) | glue logic / address decode | [P] |
| U24, U25 | 2× Intel E28F400BVT60 (© '92 '94) | main firmware 2× 512 KB → `ROM1-C.bin`; the dump files are named `MT28F400B5-T` (programmer device profile) | [P][F] |
| U26 | ST M27C256B-12F1 (UV window, label on it), DIP28 socket | boot EPROM, 32 KB | [P][F] |
| **U50** | **Hitachi HN58C66FP-25T** (date 9720), SOP28 | **8 KB parameter EEPROM** (8K×8, 250 ns), CPU address `0x600000`, busy port `0x0C`; this is the chip `doc/emulator_plan.md` §6.1 needs dumped | [P][F: size and address match] |
| U31, U32, U33, U34 | 4× Sony CXK581000BM-70LL (128K×8) | SRAM 512 KB | [P] |
| (top, next to U34) | 0.47 F 5.5 V gold supercapacitor | back-up for SRAM/RTC (exactly which chips it powers is [H]) | [P] |
| U41, U42, U43 | 3× NEC µPD71051-10 (8251A) | USART ch1 TP / ch2 PC / ch3 user | [P][F] |
| U27 | NEC µPD71054-10 (8254) | timer | [P][F] |
| U28, U29 | 2× NEC µPD71059-10 (8259A) | master/slave PIC | [P][F] |
| U44 + one near J4 | 2× ADM202JRN | RS-232 drivers | [P] |
| U5, U30, U40, U52, U53 | 74F245 / 74HC245 | data buffers | [P] |
| U2, U19, U20, U45, U49, U21 | 74F74, 74HC14, 74HC74, 74AC04 and similar | misc logic | [P] |
| U16 | small IC with a can crystal, marking unreadable | probably the RTC (MSM6242-class, ports `0x60–0x9C`) | [H] |
| S1 | push button (top left) | RESET or SELF-CHECK | [P][H] |

Compared with unit 2 (table above), this board uses NEC instead of OKI peripherals, Sony
instead of Toshiba SRAM, and two visible EPM7064 PLDs. The memory and I/O maps are the
same as far as the firmware shows.

**Reading U50.** The HN58C66 has the standard JEDEC 28C64 pin-out, so a programmer reads
it as a 28C64/AT28C64 (8192 bytes). Reading it in circuit with a SOIC-28 clip would power
the rest of the board through VCC, so it is safer to lift the chip, or at least hold /WE
high. Name the dump `FW/SRX6-CPU/1/U50_HN58C66@SOP28.BIN`; the emulator takes it as
`emu/roms/srx_c61/eeprom.bin`.

**Replacing the EEPROM (2026-11-08).** The write driver `0x6B1C` (major 5) sets what a
substitute chip must do:

- It writes **page-aligned blocks of up to 32 bytes** with interrupts off (`0xCDE08`/`0xCDE0C`),
  so the chip needs **page mode with a page of ≥ 32 bytes**. A 28C64 with no page mode (byte
  write only, e.g. Microchip 28C64A) will not work.
- It then waits `tm_wkafter(1)` (one 10 ms tick, which can be shorter) and reads **port `0x0C`
  bit 6 = write complete**. If the bit is still 0 after a second tick, it reports error `0x7919`.
  It then reads the block back and reports `0x791A` on a mismatch. Bit 6 is most likely the
  chip's **pin 1 RDY/BUSY** (open drain + pull-up); this is not traced yet.
- So the substitute should have **RDY/BUSY on pin 1**. A chip with pin 1 = NC (Microchip
  **AT28C64B**, AT28HC64B) leaves bit 6 at the pull-up level ("ready" at once). The read-back
  can then come during the write cycle (≤ 10 ms) and fail now and then.
- Candidates: the original HN58C66FP / HN58V66AFP (surplus, 32-byte page, RDY/BUSY);
  **onsemi/Catalyst CAT28C64B** (32-byte page, RDY/BUSY on pin 1, discontinued); ST M28C64
  (RDY/BUSY on pin 1, discontinued). AT28C64B-15SU (SOIC-28 300 mil) is the one in current
  production. It works only if the timing margin above holds; check by test writes.
- **The blank dumps are suspect (owner, 2026-11-08).** The programmer often reported "Device
  unavailable or error", and a read succeeded only after the chip or socket was moved. That is
  a contact fault in the SOP28 adapter, not proof of a dead chip. A read with /CE or /OE open
  returns a floating bus, which is all `FF`, so a "blank" result needs repeated identical reads
  through a reliable adapter. Do not write test data before that, or real data may be lost.
- The package must fit: compare the U50/U26 body width and lead span with the SOIC-28 300 mil
  (7.5 mm body, ~10.3 mm span) of the candidate.

---

## 3. SRX6-SIO2 — 4-channel serial mezzanine (1-674-196-11)

![SRX6-SIO2 fitted on top of the CPU board (unit 1)](../img/hw/cpu_sio2_mezzanine.jpg)

This board is the **"optional 4-channel serial board"** that the CPU firmware probes at
`0x2000000` (status register `0x2000010`, IRQ slave 6/7; architecture report §8.5). It
sits on top of the CPU board through J1/J2. It has a cut-out over the CPU, so the i486 of
unit 1 (in a socket) stays reachable at the lower right. [P][F]

```mermaid
flowchart LR
    CPUB["CPU board<br/>(via J1, J2)"]
    PLD["Altera EPM7128SLC84-15<br/>'SI01' decode / IRQ"]
    U1["PC16550DV #1"]
    U2["PC16550DV #2"]
    U3["PC16550DV #3"]
    U4["PC16550DV #4"]
    OSC["Oscillator (frequency to read)"]
    DRV["Line drivers per port<br/>RS-232 / RS-485 (SW6)"]
    SW["DIP switches SW2–SW5<br/>(one per port)"]
    P["4× DB9 male<br/>+ fuses F1–F4, filters"]

    CPUB --- PLD
    PLD --- U1 & U2 & U3 & U4
    OSC --- U1 & U2 & U3 & U4
    U1 & U2 & U3 & U4 --- DRV --- P
    SW --- DRV
```

| Item | What | Source |
|---|---|---|
| UARTs | 4× National PC16550DV (U9–U12) | [P] |
| Decoder | Altera EPM7128SLC84-15, label "SI01" | [P] |
| Mode select | SW6 silkscreen "RS232 / RS485" per port; SW2–SW5 8-way DIP per port (termination / mode?) | [P][H] |
| Connectors | 4× DB9 with fuses F1–F4 (probably on a supply pin) | [P][H] |
| Not on unit 2 | Unit 2's CPU board has no mezzanine | [O] |

---

## 4. Mother board — card-cage backplane (1-658-655-21)

![Mother board](../img/hw/mother_board.jpg)

```mermaid
flowchart LR
    PS["JAE 50P 'PS'<br/>power in"]
    CPUC["CPU connector<br/>(left, press-fit field)"]
    S1["Slot"]
    S2["Slot"]
    S3["Slot"]
    S4["Slot"]
    S5["Slot"]
    BUF["74HC245 + 74HC24x<br/>buffers"]
    BAT["Battery connectors (1), (2)"]
    TOP["Top-edge connectors<br/>(ribbons to SPD / front) [H]"]

    PS --- CPUC
    CPUC --- BUF --- S1 & S2 & S3 & S4 & S5
    BAT --- CPUC
    TOP --- CPUC
```

- One CPU connector plus **five** identical 100-pin slot connectors. This matches the five
  DPRAM windows of the CPU firmware. [P][F]
- Under each slot connector there is a column of pads/test points (70, 74, 80, 85, 89, 100).
  This may be a hard-wired slot number. [P][H]
- Two battery connectors: back-up for the absolute encoders (and the RTC/SRAM?). [P][H]
- Population in the owner's unit: SIO2 is on the CPU board; the slots hold I/O, I/O and
  SERVO; two slots are empty (room for a vision board or a second SERVO for a second
  robot — the firmware runs per-robot SVTn/TJTn tasks). [O][F][H]

---

## 5. SRX6-SERVO — servo/motion board (1-…-653-12, GCMK-M1X)

![SRX6-SERVO board](../img/hw/servo_board.jpg)

```mermaid
flowchart LR
    BP["Mother board slot<br/>(2 connectors, right edge)"]
    DP["2× Fujitsu MB8421<br/>2K×8 dual-port RAM<br/>= 16-bit DPRAM window"]
    V810["NEC µPD70732GD-25<br/>V810, 25 MHz"]
    FL["2× Intel P28F010 (U41/U42)<br/>ROM_SERVO.bin 256 KB"]
    RAM["4× SRAM (bottom left)"]
    ASIC["2× Sony CXD8477Q (U47, U54)"]
    PLD["PLDs: S6S-A1, S6S-A2B (PLCC),<br/>S6S-1…5, S6S-4A (DIP), GAL16V8B U43"]
    CAB["JAE TX3-50P front connector<br/>→ cable to Control board [H]"]
    MON["DB9: 'Servo Board Monitor'<br/>console"]
    UI["8 LEDs, 4-way DIP"]

    BP --- DP --- V810
    V810 --- FL & RAM & PLD
    PLD --- ASIC --- CAB
    V810 --- MON
    V810 --- UI
```

| Item | What | Source |
|---|---|---|
| CPU | NEC µPD70732 V810 (code at `0x00100000`) | [P][F] |
| Firmware | 2× P28F010, byte-interleaved → `ROM_SERVO.bin` ("Servo Board Monitor ©1995 Sony") | [F] |
| Host link | 2× MB8421 dual-port RAM — the CPU board sees it as one slot DPRAM window (kind byte 1) | [P][F] |
| Custom ASICs | 2× Sony CXD8477Q. Function unknown; the DSP link and the encoders are handled on the Control board, so maybe bus/link interface or timers | [P][H] |
| Front | TX3-50P (to the Control board, to confirm) and DB9 monitor port | [P][H] |

The SERVO board reaches the two DSPs' CXD8501R register blocks at V810 `0x400000` and
`0x400080`; its CPU-side DPRAM is at `0x200000` (`doc/servo_dsp_link.md`). [F] The monitor's
`AMP ERROR(axis 1/2)` / `(axis 3/4)` texts mean **DSP 1 (axes 1, 2)** and **DSP 2 (axes 3,
4)**. [F]

---

## 6. SRX6-I/O — 24 V digital I/O board (1-658-654-21, GCMK-G3X)

| Side A | Side B |
|---|---|
| ![SRX6-I/O side A](../img/hw/io_board_a.jpg) | ![SRX6-I/O side B](../img/hw/io_board_b.jpg) |

The two photos show the **two sides** of the board: B is a mirror image of A, with the
front connectors on the right and the backplane field on the left. Photocouplers are
fitted on both sides (even ISO numbers on A, odd on B). [P]

```mermaid
flowchart LR
    BP["Mother board slot<br/>TX15-100P"]
    LOG["Bus interface<br/>74HC latches / buffers,<br/>EPM7032-15 footprint"]
    INP["24 inputs PHT1–24<br/>photocouplers ISO049–096<br/>+ RC filters"]
    OUT["Outputs<br/>photocouplers ISO001–048<br/>+ transistor drivers Q…"]
    CIN["CN-IN<br/>F1 24 V 0.5 A"]
    COUT["CN-OUT<br/>F2 24 V 0.5 A"]
    P24["EXT.24V / 0V.COM<br/>JP2, JP3 (internal vs external 24 V)"]

    BP --- LOG
    LOG --- INP --- CIN
    LOG --- OUT --- COUT
    P24 --- CIN & COUT
```

- 24 inputs (PHT1–PHT24) are certain. There are about 48 photocouplers in the input area
  (ISO049–096, both sides). That suggests two per input (either-polarity inputs?) or a
  second group of 24 inputs. [P][H]
- Outputs: photocouplers ISO001–048 plus transistor drivers. The exact output count is to
  be confirmed. [P][H]
- The firmware sees the board as slot **kind 3**; it is scanned by SYST (`0x108FC`). [F]

---

## 7. Control board — DSP current controller (1-659-417-12, PCB 412310028)

![Control board](../img/hw/control_board.jpg)

**One** board per controller. It plugs into the drive backplane together with the four
drivers. [O] Its two EPROMs are the dumps in `FW/SERVO_IO/1/` (folder name kept for
history). Firmware analysis: `doc/control_board_firmware.md`.

```mermaid
flowchart TB
    HOST["Host link (50-pin, front)<br/>from SERVO [H]"]
    subgraph CH1["Channel 1 = axes A, B"]
        DSP1["ADSP-2115 #1"]
        ROM1["27C512 'C6A06 V2.07'"]
        ASIC1["Sony CXD8501R<br/>mailbox + 6× PWM + I/O"]
        ADC1["AD7874<br/>4-ch 12-bit simultaneous ADC"]
        GAL1["GAL20V8B 'WEP089'"]
    end
    subgraph CH2["Channel 2 = axes C, D"]
        DSP2["ADSP-2115 #2"]
        ROM2["27C512 'C6A06 V2.07'"]
        ASIC2["Sony CXD8501R"]
        ADC2["AD7874"]
        GAL2["GAL20V8B 'WEP089'"]
    end
    BPC["TX15-120P → drive backplane<br/>PWM out, current sense in,<br/>module ID, feedback"]

    HOST --- ASIC1 & ASIC2
    ROM1 -- boot --> DSP1
    ROM2 -- boot --> DSP2
    DSP1 --- GAL1 --- ASIC1 & ADC1
    DSP2 --- GAL2 --- ASIC2 & ADC2
    ASIC1 & ASIC2 & ADC1 & ADC2 --- BPC
```

| Item | What | Source |
|---|---|---|
| DSP | 2× Analog Devices ADSP-2115 KP-66, booting from byte-wide EPROM | [P][F] |
| EPROM | 2× ST 27C512 "C6A06 V2.07" — **identical** images (`U7`/`U18` dumps, same MD5) | [P][F] |
| ADC | 2× AD7874AR: 4-channel, 12-bit, simultaneous sampling; read as 4 consecutive words at DSP DM `0x3400` | [P][F] |
| ASIC | 2× Sony CXD8501R: per-DSP peripheral at DM `0x3000–0x303F` (host mailbox, 6 PWM compare registers, status) | [P][F][H] |
| Glue | 2× GAL20V8B "WEP089", 74HC08/HC32/LS07 | [P] |
| Connectors | TX15-120P (top) to the drive backplane; 50-pin header (front) — host cable or feedback, to confirm | [P][H] |

Each DSP drives **two motors**. Its AD7874 gives 2 phase currents per motor, and its
CXD8501R produces 3 PWM phases per motor (6 compare registers). [F][H]

---

## 8. Drive section — drivers and backplane

Seen only in the chassis photo (§1). Four identical driver modules (each with a choke and a
large bulk capacitor) and the Control board plug into one long backplane. That backplane
takes motor power in and carries the feedback connector. [O][P] Each driver reports a
4-bit module ID to the DSP (DM `0x3030`, firmware selects current-scaling constants by it).
[F][H]

---

## 9. SPD panel board — over-speed detector and safety relays (1-661-736-13)

![SPD panel board](../img/hw/spd_panel_board.jpg)

```mermaid
flowchart LR
    CONN["J12 50-pin ribbon (top)<br/>+ right-edge connector<br/>→ Mother board / CPU [H]"]
    PLD1["Altera EPM7160SLC84-10<br/>(U5)"]
    PLD2["Altera EPM7160SLC84-10<br/>(U6)"]
    WD["74HC123 one-shots,<br/>74HC14 / 74HC04"]
    OPT["≈16 photocouplers<br/>IS001…"]
    REL["≈15 signal relays<br/>(24 V coils)"]
    SAFE["3 force-guided<br/>safety relays"]
    FRONT["Front: DB25, DB15, DB9 (female)<br/>with filters"]
    BATT["BATT1–3, FAN1/2,<br/>status LEDs"]
    K["Contactors / brakes [H]"]

    CONN --- PLD1 & PLD2
    PLD1 & PLD2 --- WD
    OPT --- PLD1 & PLD2
    FRONT --- OPT
    PLD1 & PLD2 --- REL --- SAFE --> K
    BATT --- CONN
```

- The two EPM7160s implement the **over-speed detector** behind **E400 "SPD over speed"**.
  The SMART option's **Drive Safety Switch** (E401 "DSS off") is also wired through this
  board. [F][H]
- 74HC123 one-shots: hardware watchdog/heartbeat check. [H]
- The front DB25/DB15/DB9 carry the external safety and emergency-stop circuits and
  probably the I/O or TP lines. To be confirmed by continuity test. [H]
- A design file `SPD_panel_relays.dch` exists on the workstation (AGENTS.md §2.7).

---

## 10. Open questions (hardware)

1. Confirm the 50-pin cable from the SERVO front (TX3-50P) goes to the Control board
   (firmware says SERVO addresses both DSP windows at `0x400000/0x400080`).
2. Confirm the encoder lines stop at the Control board (firmware points that way —
   `doc/servo_dsp_link.md` §6): serial ABS → DSP SPORT0, A/B/UVW → CXD8501R?
3. Which Mother-board slot is which DPRAM window, and what are the slot pads for?
4. SIO2 oscillator frequency and the meaning of SW2–SW6.
5. Why ~48 photocouplers for 24 inputs on SRX6-I/O; how many outputs.
6. Pin-out of the SPD front connectors (DB25 / DB15 / DB9).
