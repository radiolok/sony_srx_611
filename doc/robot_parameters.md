# SRX-611 robot parameters (`.CTR` block): known values

Both CPU-board parameter EEPROMs read blank (see `doc/SRX-611_firmware_architecture.md`
§8.7 and `doc/emulator_plan.md` §6.1). This file collects every **real** value we have, so
the parameter block can be rebuilt, either through the teach-pendant parameter screens
(in the emulator or on the unit) or by a generator script.

## 1. Factory plate on the controller (photo 2026-11-08)

![Rear plates, controller C61-1039](../img/hw/plate_c61-1039.png)

"ASSEMBLY ROBOT" plate:

| Field | Value |
|---|---|
| Model | **SRX-C61 (SRX-611)** |
| R.No. (robot number) | **82790** |
| C.No. (controller number) | **C61-1039** |
| MFD | '98.3 (March 1998) |
| Supply | 200–230 V 1-phase 50/60 Hz, 7.5–6.5 A |
| Plate part no. | 4-702-141-02 |

"ROBOT PARAMETERS" plate (factory calibration of **this** arm, adjust date '98.3):

| Group | Axis | Value | Probable unit [H] |
|---|---|---|---|
| HOME PARA. | θ1 or X | **202108** | encoder counts |
| HOME PARA. | θ2 or Y | **172675** | encoder counts |
| HOME PARA. | Z | **20190** | encoder counts |
| HOME PARA. | R | **0** | encoder counts |
| ARM LENGTH | L1 | **349.883** | mm (nominal 350) |
| ARM LENGTH | L2 | **249.755** | mm (nominal 250) |

These values are specific to the arm. A `.CTR` taken from another controller (for example
Debrecen) gives everything else, but its HOME PARA and ARM LENGTH must be replaced with the
values above.

The plate is on **unit 1**, the controller with the socketed CPU (CPU board 1-658-652-11,
EEPROM U50; owner, 2026-11-08). The owner has **only one arm**, so these are the calibration
values for that arm: robot 82790, matched at the factory with controller C61-1039. Unit 2
(CPU board 1-676-745-11) has no matching arm. Its firmware dump (`FW/SRX6-CPU/2/`) is the one
under analysis, but the parameters above apply to it once it drives this arm.

## 2. Where the values go in the firmware

The pendant parameter menus exist in the ROM string block (file offsets, used from RAM, see
AGENTS §8.1): `SYSTEM OFFSET` `0xD2D31`, `SERVO PARA` `~0xD2D4C`, `ARM LENGTH` `0xD2D65`,
`HOME PARA` `0xD2D81`, `HOME OFF` `0xD3956`, `HOME POSI` `0xD398E`, `AUTO MEASURE`,
`VIB_CTRL`, `SERIAL No.:` `0xD3587`, `DEF ROBOT NUM`, `SAFETY SPEC`, ` MODEL: SRX-` `0xD0898`.
LUNA also has `GETARML` / `CHGARML` (read and change the arm length).

The fields that E050 checks, in order (the line number shown with E050), are listed in
`doc/SRXMONIE_help.md` §E050: 100 MODEL, 101 SERIAL No., 102 TP language, 103 SAFETY SPEC,
104 DEF ROBOT NUM, 105 ROBOT KIND, 106 INTERFERE, 107 INTERFERE RATIO, 108 REDUCTION RATIO,
109 ENCODER PULSE, 110 CNTR DIR, 111 SLOT/AXIS, 112 HOME OFFSET, 113 HOME POSITION,
114 HOME ORDER, 115 Motion Data Number, 116 SERVO PARAMETER.

Open: map each field to its offset in RAM `0x4A24`–`0x622C` (from `sys_config_validate`
`0x8BD4`) and find out whether the plate's HOME PARA values are HOME OFFSET (112) or HOME
POSITION (113).

## 3. Other known values

| Item | Value | Source |
|---|---|---|
| Arm 1 / arm 2 / Z / R | 350 / 250 mm, Z 150 mm, R ±360° | README §1.1, Kapusi 2022 |
| Joint ranges | axis 1 220°, axis 2 ±150° | Kapusi 2022 (from the manual) |
| Axes on servo slots | 4 axes on one SRX6-SERVO slot | owner, `hardware_overview.md` |
