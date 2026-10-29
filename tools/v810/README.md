# tools/v810 — NEC V810 disassembler (SRX6-SERVO firmware)

`v810dis.py` is a small linear-sweep disassembler for the NEC V810 (µPD70732), written for
`FW/SRX6-SERVO/ROM_SERVO.bin`. Python 3, no dependencies. Used for
`doc/servo_dsp_link.md`.

The servo firmware copies its ROM to RAM at address 0 and runs there, and keeps
`gp = 0x2BAEC`, so use `--base 0 --seed gp=0x2BAEC`. Code ends before `0x17000`; strings
and data follow from `0x21000`.

```sh
R=FW/SRX6-SERVO/ROM_SERVO.bin
O="--base 0 --seed gp=0x2BAEC"
python3 tools/v810/v810dis.py dis    $R $O --end 0x17000 -o servo.asm     # full listing
python3 tools/v810/v810dis.py dis    $R $O --start 0x0D8C --end 0x0E3C    # a range
python3 tools/v810/v810dis.py consts $R 0x400000 0x4000FF $O --end 0x17000  # address constants
python3 tools/v810/v810dis.py refs   $R 0x400000 0x4000FF $O --end 0x17000 --ctx 4
python3 tools/v810/v810dis.py imm    $R 0x3865 0x38C5 $O --end 0x17000     # immediates
```

- `dis`: listing with `sub_` labels for JAL targets; loads and stores through a register
  with a known value get the absolute address as a comment.
- `consts`: flow-insensitive search for `movhi H,r0,rX` followed by `movea/addi L,rX,…` or
  `ld/st disp[rX]`. It also catches addresses that are merged at branch targets, which the
  straight-line tracker drops.
- `refs`: accesses whose tracked address falls in a range.
- `imm`: 32-bit instructions with a given 16-bit immediate.

Limits: linear sweep (data, jump tables and padding decode as code); constant tracking
resets at branch targets; FPU and bit-string instructions are named but not detailed. The
encoding follows the public V810 architecture (formats I–VII); the reset vector and the
start-up code decode correctly, which was the check used.
