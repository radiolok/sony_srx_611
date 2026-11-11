# Notes on Kapusi et al. 2022 — "Application of Deep Learning in the Deployment of an Industrial SCARA Machine for Real-Time Object Detection"

Source: `books/Application_of_Deep_Learning_in_the_Deployment_of_.pdf`
(T. P. Kapusi, T. I. Erdei, G. Husi, A. Hajdu — *Robotics* 2022, 11, 69, University of
Debrecen, CPS-LAB). 20 pages. Read 2026-11-08.

## Summary

The paper is about **YOLO object detection** (v3/v4/tiny) trained on images rendered from
a 3D CAD model. The SRX-611 is only the host machine; its controller is used unchanged. The
paper contains **nothing about the firmware, protocols or controller internals**. About
80 % of it is about dataset synthesis (Blender) and YOLO training metrics.

## Facts relevant to this project

| Item | Paper says | Our data | Comment |
|---|---|---|---|
| Arm lengths | 350 / 250 mm, Z 150 mm, R ±360° | same (README §1.1) | confirms the L6015 variant |
| **Joint ranges** | **axis 1: 220°, axis 2: ±150°** | not in README | taken from the manual [8]; if "220°" is the total range, axis 1 ≈ ±110°. Useful for the emulator's plant/visualisation limits |
| Speeds | Z 770 mm/s, R 1150°/s; cycle 0.6 s | same | — |
| Encoders | "incremental encoders that retain position when de-energised" | serial **absolute** encoders (`doc/abs_encoder_protocol.md`) | the paper's wording is loose; "retain position" implies absolute/battery-backed. No conflict with the firmware |
| CPU | i486DX2 50 MHz | same | the paper says the controller "is written around DOS", which is wrong (pSOS+/386) |
| Teach pendant | their unit had **no TP**; programmed from the PC only | — | shows the controller runs with no pendant attached (TP absent → no hard fault) |
| PC link | SRX PLATFORM (SRXMONIE) under **Windows XP in VMware Player**, through a **CH341 USB-RS232** adapter | `doc/SRXWIN_protocol.md` (9600 8N2, DSR handshake) | first-hand confirmation that the GUI works through a USB-serial adapter and a VM, so the protocol has no tight timing. Good news for SRXWIN-NG stage 1 and for testing the emulator's pty against the original GUI |
| Workflow | compile `.PON` → `.DAT` in the Compile menu, then **Send**, then the **physical Start button** | matches §2.5 | — |
| LUNA examples | `DO <point>` moves to a point; `DO L(2, ON/OFF)` gripper air; `DO L8 (ON/OFF)` gripper open/close; `DO L5 (ON)` conveyor; `PALLET: PAL1` declaration | see `doc/LUNA_token_map.md` | site-specific output numbers (L2, L5, L8), not a standard. The listing is a screenshot; the text gives no full program |
| Peripherals | electro-pneumatic 2-finger gripper; PARO QE 01 31-6000 conveyor with 4 stops and inductive sensors | — | — |

## 3D CAD model (relevant for emulator visualisation)

- The authors built a detailed **3D model of the SRX-611** in Trimble SketchUp (more than
  1500 sub-models), exported it to **`.obj`**, and rendered it in **Blender** (polygon
  reduction, HSV colours taken from photos, no textures).
- *Data Availability Statement*: "available on request from the corresponding author."
  It is worth asking them for the `.obj`. It could serve as the mesh for a 3D view of the
  emulated arm (see `doc/emulator_plan.md`). Otherwise we build a simple parametric model
  from the dimensions above.

## Not useful

The related-work section (RNN obstacle avoidance and similar), the YOLO architecture, the
training metrics (mAP, loss curves) and the hardware of their lab PCs.
