# tools/adsp — ADSP-21xx boot EPROM tools

`adsp21xx.py` unpacks and disassembles ADSP-2101/2105/2115 boot EPROMs. It was written for
the two ADSP-2115 DSPs of the SRX-C61 Control board (`FW/SERVO_IO/1/U7_*.BIN`,
`U18_*.BIN`); see `doc/control_board_firmware.md`.

Python 3 only, no dependencies.

```sh
R='FW/SERVO_IO/1/U7_M27C512@DIP28.BIN'
python3 tools/adsp/adsp21xx.py pages $R                              # list boot pages
python3 tools/adsp/adsp21xx.py dis   $R -o FW/SERVO_IO/1/U7_dis.asm  # all pages
python3 tools/adsp/adsp21xx.py dis   $R -p 1                         # one page
python3 tools/adsp/adsp21xx.py xref  $R -o FW/SERVO_IO/1/U7_xref.md  # DM access tables
```

What it does:

- splits the EPROM into boot pages (8 KB stride, length from byte 3, 4 bytes per word);
- decodes every instruction (port of MAME's `2100dasm.cpp`, BSD-3-Clause, Aaron Giles);
- labels branch/call targets and marks the interrupt-vector slots;
- tracks I/M registers loaded with constants, including post-modify and one-instruction
  `DO` loops, and comments each indirect access with its DM address and region;
- names the memory-mapped control registers (`SYSCNTL`, `DM_WAIT`, SPORT, timer);
- assumes page-0 M register values in later pages, because a BFORCE soft reboot keeps
  them (`--no-seed` to disable);
- `xref`: tables of direct and resolved indirect DM accesses, flag-pin changes and the
  most-called subroutines.

Limits: linear sweep (PM data tables show up as code); register tracking resets at
branch targets.
