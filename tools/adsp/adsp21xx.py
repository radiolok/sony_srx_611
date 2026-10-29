#!/usr/bin/env python3
"""ADSP-21xx boot-EPROM unpacker and disassembler (ADSP-2101/2105/2115 family).

Built for the Sony SRX-611 Control board, which has two ADSP-2115 DSPs, each booting
from its own 27C512 EPROM (in this repo: FW/SERVO_IO/1/U7_*.BIN, U18_*.BIN).

Boot EPROM format (ADSP-2101/2115, MMAP=0):
  * boot pages sit every 8 KB (BPAGE 0..7 selects EPROM A13..A15);
  * each 24-bit PM word takes 4 bytes: [hi, mid, lo, pad];
  * the pad byte of word 0 holds the page length: words = (byte3 + 1) * 8;
  * the page is loaded into internal PM from address 0; the program can reboot into
    another page by writing BPAGE + BFORCE to the System Control register (DM 0x3FFF).

The instruction decoder is a Python port of MAME's ADSP-21xx disassembler
(src/devices/cpu/adsp2100/2100dasm.cpp, BSD-3-Clause, copyright Aaron Giles).

Usage:
  adsp21xx.py pages ROM.BIN                 list boot pages
  adsp21xx.py dis ROM.BIN [-p N] [-o FILE]  disassemble page N (default: all pages)
  adsp21xx.py xref ROM.BIN [-p N]           DM/control-register/flag usage summary
"""
import argparse
import collections
import sys

# ---------------------------------------------------------------- tables (from MAME)
FLAG_CHANGE = ["", "TOGGLE %s ", "RESET %s ", "SET %s "]
MODE_CHANGE = ["", "", "DIS %s ", "ENA %s "]
ALU_XOP = ["AX0", "AX1", "AR", "MR0", "MR1", "MR2", "SR0", "SR1"]
ALU_YOP = ["AY0", "AY1", "AF", "0"]
ALU_DST = ["AR", "AF", "NONE"]
MAC_XOP = ["MX0", "MX1", "AR", "MR0", "MR1", "MR2", "SR0", "SR1"]
MAC_YOP = ["MY0", "MY1", "MF", "0"]
MAC_DST = ["MR", "MF", "NONE"]
SHIFT_XOP = ["SI", "??", "AR", "MR0", "MR1", "MR2", "SR0", "SR1"]
REG_GRP = [
    ["AX0", "AX1", "MX0", "MX1", "AY0", "AY1", "MY0", "MY1", "SI", "SE", "AR", "MR0", "MR1", "MR2", "SR0", "SR1"],
    ["I0", "I1", "I2", "I3", "M0", "M1", "M2", "M3", "L0", "L1", "L2", "L3", "??", "??", "PMOVLAY", "DMOVLAY"],
    ["I4", "I5", "I6", "I7", "M4", "M5", "M6", "M7", "L4", "L5", "L6", "L7", "??", "??", "??", "??"],
    ["ASTAT", "MSTAT", "SSTAT", "IMASK", "ICNTL", "CNTR", "SB", "PX", "RX0", "TX0", "RX1", "TX1", "IFC", "OWRCNTR", "??", "??"],
]
DUAL_XREG = ["AX0", "AX1", "MX0", "MX1"]
DUAL_YREG = ["AY0", "AY1", "MY0", "MY1"]
CONDITION = ["IF EQ ", "IF NE ", "IF GT ", "IF LE ", "IF LT ", "IF GE ", "IF AV ", "IF NOT AV ",
             "IF AC ", "IF NOT AC ", "IF NEG ", "IF POS ", "IF MV ", "IF NOT MV ", "IF NOT CE ", ""]
DO_CONDITION = ["NE", "EQ", "LE", "GT", "GE", "LT", "NOT AV", "AV", "NOT AC", "AC", "POS", "NEG",
                "NOT MV", "MV", "CE", "FOREVER"]
ALUMAC_OP = [
    ("", ""),
    ("%s = %s * %s (RND)", "%s = %s * %s (RND)"),
    ("%s = MR + %s * %s (RND)", "%s = MR + %s * %s (RND)"),
    ("%s = MR - %s * %s (RND)", "%s = MR - %s * %s (RND)"),
    ("%s = %s * %s (SS)", "%s = 0"),
    ("%s = %s * %s (SU)", "%s = %s * %s (SU)"),
    ("%s = %s * %s (US)", "%s = %s * %s (US)"),
    ("%s = %s * %s (UU)", "%s = %s * %s (UU)"),
    ("%s = MR + %s * %s (SS)", "%s = MR + %s * %s (SS)"),
    ("%s = MR + %s * %s (SU)", "%s = MR + %s * %s (SU)"),
    ("%s = MR + %s * %s (US)", "%s = MR + %s * %s (US)"),
    ("%s = MR + %s * %s (UU)", "%s = MR + %s * %s (UU)"),
    ("%s = MR - %s * %s (SS)", "%s = MR - %s * %s (SS)"),
    ("%s = MR - %s * %s (SS)", "%s = MR - %s * %s (SS)"),
    ("%s = MR - %s * %s (US)", "%s = MR - %s * %s (US)"),
    ("%s = MR - %s * %s (UU)", "%s = MR - %s * %s (UU)"),
    ("!%s = %s", "%s = 0"),
    ("!%s = %s + 1", "%s = 1"),
    ("%s = %s + %s + C", "%s = %s + %s + C"),
    ("%s = %s + %s", "%s = %s"),
    ("!%s = NOT %s", "!%s = NOT %s"),
    ("!%s = -%s", "!%s = -%s"),
    ("%s = %s - %s + C - 1", "%s = %s + C - 1"),
    ("%s = %s - %s", "%s = %s - %s"),
    ("!%s = %s - 1", "%s = -1"),
    ("!%s = %s - %s", "%s = -%s"),
    ("!%s = %s - %s + C - 1", "%s = -%s + C - 1"),
    ("%s = NOT %s", "%s = NOT %s"),
    ("%s = %s AND %s", "%s = %s AND %s"),
    ("%s = %s OR %s", "%s = %s OR %s"),
    ("%s = %s XOR %s", "%s = %s XOR %s"),
    ("%s = ABS %s", "%s = ABS %s"),
]
SHIFT_OP = ["SR = LSHIFT %s (HI)", "SR = SR OR LSHIFT %s (HI)", "SR = LSHIFT %s (LO)", "SR = SR OR LSHIFT %s (LO)",
            "SR = ASHIFT %s (HI)", "SR = SR OR ASHIFT %s (HI)", "SR = ASHIFT %s (LO)", "SR = SR OR ASHIFT %s (LO)",
            "SR = NORM %s (HI)", "SR = SR OR NORM %s (HI)", "SR = NORM %s (LO)", "SR = SR OR NORM %s (LO)",
            "SE = EXP %s (HI)", "SE = EXP %s (HIX)", "SE = EXP %s (LO)", "SB = EXPADJ %s"]
SHIFT_BY_OP = ["SR = LSHIFT %s BY %d (HI)", "SR = SR OR LSHIFT %s BY %d (HI)",
               "SR = LSHIFT %s BY %d (LO)", "SR = SR OR LSHIFT %s BY %d (LO)",
               "SR = ASHIFT %s BY %d (HI)", "SR = SR OR ASHIFT %s BY %d (HI)",
               "SR = ASHIFT %s BY %d (LO)", "SR = SR OR ASHIFT %s BY %d (LO)"] + ["???"] * 8
CONSTANTS = ["$0001", "$FFFE", "$0002", "$FFFD", "$0004", "$FFFB", "$0008", "$FFF7",
             "$0010", "$FFEF", "$0020", "$FFDF", "$0040", "$FFBF", "$0080", "$FF7F",
             "$0100", "$FEFF", "$0200", "$FDFF", "$0400", "$FBFF", "$0800", "$F7FF",
             "$1000", "$EFFF", "$2000", "$DFFF", "$4000", "$BFFF", "$8000", "$7FFF"]

# ---------------------------------------------------------------- ADSP-2101/2115 map
# Interrupt vectors (MMAP=0): 4 PM words each.
VECTORS = {0x00: "RESET", 0x04: "IRQ2", 0x08: "SPORT0_TX", 0x0C: "SPORT0_RX",
           0x10: "IRQ1_SPORT1_TX", 0x14: "IRQ0_SPORT1_RX", 0x18: "TIMER"}
# Memory-mapped control registers in DM (ADSP-2101/2115 data sheet; verify against it).
CTRL_REGS = {
    0x3FFF: "SYSCNTL", 0x3FFE: "DM_WAIT", 0x3FFD: "TPERIOD", 0x3FFC: "TCOUNT", 0x3FFB: "TSCALE",
    0x3FFA: "SP0_MC_RX_HI", 0x3FF9: "SP0_MC_RX_LO", 0x3FF8: "SP0_MC_TX_HI", 0x3FF7: "SP0_MC_TX_LO",
    0x3FF6: "SP0_CTRL", 0x3FF5: "SP0_SCLKDIV", 0x3FF4: "SP0_RFSDIV", 0x3FF3: "SP0_AUTOBUF",
    0x3FF2: "SP1_CTRL", 0x3FF1: "SP1_SCLKDIV", 0x3FF0: "SP1_RFSDIV", 0x3FEF: "SP1_AUTOBUF",
}


def dm_region(addr):
    """Name the ADSP-2115 data-memory region an address falls into."""
    if addr >= 0x3C00:
        return "ctrl"
    if 0x3800 <= addr < 0x3A00:
        return "int_ram"
    if addr < 0x0400:
        return "ext_DWAIT0"
    if addr < 0x0800:
        return "ext_DWAIT1"
    if addr < 0x3000:
        return "ext_DWAIT2"
    if addr < 0x3400:
        return "ext_DWAIT3"
    if addr < 0x3800:
        return "ext_DWAIT4"
    return "reserved"


def dm_name(addr):
    if addr in CTRL_REGS:
        return CTRL_REGS[addr]
    return None


# ---------------------------------------------------------------- boot pages
PAGE_STRIDE = 0x2000


def boot_pages(rom):
    """Return {page: [24-bit words]} for every boot page that holds data."""
    pages = {}
    for p in range(len(rom) // PAGE_STRIDE):
        base = p * PAGE_STRIDE
        if all(b == 0xFF for b in rom[base:base + 4]):
            continue
        n = (rom[base + 3] + 1) * 8
        words = []
        for i in range(n):
            o = base + i * 4
            words.append(rom[o] << 16 | rom[o + 1] << 8 | rom[o + 2])
        pages[p] = words
    return pages


# ---------------------------------------------------------------- decoder
def BIT(v, pos, n=1):
    return (v >> pos) & ((1 << n) - 1)


def _fmt(s, *args):
    return s % args[:s.count("%")]


def _alumac(dest, op):
    idx = BIT(op, 13, 5)
    if BIT(idx, 4):
        xop, yop, dst = ALU_XOP[BIT(op, 8, 3)], ALU_YOP[BIT(op, 11, 2)], ALU_DST[dest]
    else:
        xop, yop, dst = MAC_XOP[BIT(op, 8, 3)], MAC_YOP[BIT(op, 11, 2)], MAC_DST[dest]
    s = ALUMAC_OP[idx][1 if BIT(op, 11, 2) == 3 else 0]
    if s.startswith("!"):
        return _fmt(s[1:], dst, yop, xop)
    return _fmt(s, dst, xop, yop)


def _aluconst(dest, op):
    idx = BIT(op, 13, 5)
    if BIT(idx, 4):
        xop, dst = ALU_XOP[BIT(op, 8, 3)], ALU_DST[dest]
        cval = CONSTANTS[BIT(op, 5, 3) | BIT(op, 11, 2) << 3]
    else:
        xop = MAC_XOP[BIT(op, 8, 3)]
        cval, dst = xop, MAC_DST[dest]
    s = ALUMAC_OP[idx][1 if BIT(op, 11, 2) == 3 else 0]
    if s.startswith("!"):
        return _fmt(s[1:], dst, cval, xop)
    return _fmt(s, dst, xop, cval)


class Insn:
    """One decoded instruction plus the facts the analysis passes need."""
    __slots__ = ("addr", "op", "text", "target", "kind", "cond", "dm_abs", "dm_write",
                 "imm_reg", "imm_val", "ireg", "mreg", "dm_ind_write", "flags", "eff", "rep")

    def __init__(self, addr, op):
        self.addr, self.op = addr, op
        self.text = ""
        self.target = None      # branch / call / DO target
        self.kind = None        # 'jump', 'call', 'do', 'rts', 'rti', 'ijump', 'icall', 'idle'
        self.cond = True        # False = unconditional
        self.dm_abs = None      # DM(addr) direct access
        self.dm_write = False
        self.imm_reg = None     # register loaded by immediate
        self.imm_val = None
        self.ireg = None        # I register used for an indirect DM access
        self.mreg = None        # its post-modify M register
        self.eff = None         # effective DM address when the I register is known
        self.rep = None         # (count, last address) for a one-instruction DO loop body
        self.dm_ind_write = False
        self.flags = None       # FL0/FL1/FL2/FLAG_OUT change text


def decode(op, addr=0):
    d = Insn(addr, op)
    top = BIT(op, 16, 8)
    t = None
    if top == 0x00:
        t = "NOP" if op == 0 else "??? (%06X)" % op
    elif top == 0x01:
        t = ("%s = IO($%X)" % (REG_GRP[0][BIT(op, 0, 4)], BIT(op, 4, 11)) if not BIT(op, 15)
             else "IO($%X) = %s" % (BIT(op, 4, 11), REG_GRP[0][BIT(op, 0, 4)])) + "  ; 218x only"
    elif top == 0x02:
        if BIT(op, 12, 4) == 0:
            f = (FLAG_CHANGE[BIT(op, 4, 2)].replace("%s", "FLAG_OUT") + FLAG_CHANGE[BIT(op, 6, 2)].replace("%s", "FL0")
                 + FLAG_CHANGE[BIT(op, 8, 2)].replace("%s", "FL1") + FLAG_CHANGE[BIT(op, 10, 2)].replace("%s", "FL2"))
            t = CONDITION[BIT(op, 0, 4)] + f
            d.flags = f.strip()
        elif BIT(op, 4, 12) == 0x800:
            t = "IDLE" if BIT(op, 0, 4) == 0 else "IDLE(%d)" % (BIT(op, 0, 4) << 4)
            d.kind = "idle"
        else:
            t = "??? (%06X)" % op
    elif top == 0x03:
        d.target = BIT(op, 4, 12) | BIT(op, 2, 2) << 12
        d.kind = "call" if BIT(op, 0) else "jump"
        t = ("IF FLAG_IN " if BIT(op, 1) else "IF NOT FLAG_IN ") + d.kind.upper() + " $%04X" % d.target
    elif top == 0x04:
        if BIT(op, 5, 11) == 0:
            t = ""
            if BIT(op, 4):
                t += "POP PC "
            if BIT(op, 3):
                t += "POP LOOP "
            if BIT(op, 2):
                t += "POP CNTR "
            if BIT(op, 0, 2) == 2:
                t += "PUSH STAT "
            elif BIT(op, 0, 2) == 3:
                t += "POP STAT "
            t = t.strip() or "NOP"
        else:
            t = "??? (%06X)" % op
    elif top == 0x05:
        t = "IF MV SAT MR" if BIT(op, 0, 16) == 0 else "??? (%06X)" % op
    elif top == 0x06:
        t = ("DIVS %s,%s" % (ALU_YOP[BIT(op, 11, 2)], ALU_XOP[BIT(op, 8, 3)])
             if (op & 0x00E0FF) == 0 else "??? (%06X)" % op)
    elif top == 0x07:
        t = "DIVQ %s" % ALU_XOP[BIT(op, 8, 3)] if (op & 0x00F8FF) == 0x001000 else "??? (%06X)" % op
    elif top == 0x08:
        t = "??? (%06X)" % op
    elif top == 0x09:
        if BIT(op, 5, 11) == 0:
            i = BIT(op, 2, 3)
            t = "MODIFY (I%d,M%d)" % (i, (i & 4) + BIT(op, 0, 2))
        else:
            t = "??? (%06X)" % op
    elif top == 0x0A:
        if BIT(op, 5, 11) == 0:
            d.kind = "rti" if BIT(op, 4) else "rts"
            d.cond = BIT(op, 0, 4) != 15
            t = CONDITION[BIT(op, 0, 4)] + d.kind.upper()
        else:
            t = "??? (%06X)" % op
    elif top == 0x0B:
        if BIT(op, 8, 8) == 0:
            d.kind = "icall" if BIT(op, 4) else "ijump"
            d.cond = BIT(op, 0, 4) != 15
            t = CONDITION[BIT(op, 0, 4)] + ("CALL" if BIT(op, 4) else "JUMP") + " (I%d)" % (4 + BIT(op, 6, 2))
        else:
            t = "??? (%06X)" % op
    elif top == 0x0C:
        t = "".join(MODE_CHANGE[BIT(op, p, 2)].replace("%s", n) for p, n in
                    ((4, "SEC_REG"), (6, "BIT_REV"), (8, "AV_LATCH"), (10, "AR_SAT"),
                     (12, "M_MODE"), (14, "TIMER"), (2, "G_MODE"))).strip()
    elif top == 0x0D:
        if BIT(op, 12, 4) == 0:
            t = "%s = %s" % (REG_GRP[BIT(op, 10, 2)][BIT(op, 4, 4)], REG_GRP[BIT(op, 8, 2)][BIT(op, 0, 4)])
        else:
            t = "??? (%06X)" % op
    elif top == 0x0E:
        if (op & 0x0080F0) == 0:
            t = CONDITION[BIT(op, 0, 4)] + SHIFT_OP[BIT(op, 11, 4)] % SHIFT_XOP[BIT(op, 8, 3)]
        else:
            t = "??? (%06X)" % op
    elif top == 0x0F:
        if not BIT(op, 15):
            s = SHIFT_BY_OP[BIT(op, 11, 4)]
            sh = op & 0xFF
            sh = sh - 256 if sh & 0x80 else sh
            t = s % (SHIFT_XOP[BIT(op, 8, 3)], sh) if "%" in s else s
        else:
            t = "??? (%06X)" % op
    elif top == 0x10:
        if not BIT(op, 15):
            t = SHIFT_OP[BIT(op, 11, 4)] % SHIFT_XOP[BIT(op, 8, 3)] + ", %s = %s" % (
                REG_GRP[0][BIT(op, 4, 4)], REG_GRP[0][BIT(op, 0, 4)])
        else:
            t = "??? (%06X)" % op
    elif top == 0x11:
        t = SHIFT_OP[BIT(op, 11, 4)] % SHIFT_XOP[BIT(op, 8, 3)]
        r, i, m = REG_GRP[0][BIT(op, 4, 4)], 4 + BIT(op, 2, 2), 4 + BIT(op, 0, 2)
        t += ", PM(I%d,M%d) = %s" % (i, m, r) if BIT(op, 15) else ", %s = PM(I%d,M%d)" % (r, i, m)
    elif top in (0x12, 0x13):
        t = SHIFT_OP[BIT(op, 11, 4)] % SHIFT_XOP[BIT(op, 8, 3)]
        b = 4 if BIT(op, 16) else 0
        r, i, m = REG_GRP[0][BIT(op, 4, 4)], b + BIT(op, 2, 2), b + BIT(op, 0, 2)
        d.ireg, d.mreg, d.dm_ind_write = i, m, bool(BIT(op, 15))
        t += ", DM(I%d,M%d) = %s" % (i, m, r) if BIT(op, 15) else ", %s = DM(I%d,M%d)" % (r, i, m)
    elif 0x14 <= top <= 0x17:
        d.target, d.kind = BIT(op, 4, 14), "do"
        t = "DO $%04X UNTIL %s" % (d.target, DO_CONDITION[BIT(op, 0, 4)])
    elif 0x18 <= top <= 0x1F:
        d.target = BIT(op, 4, 14)
        d.kind = "call" if BIT(op, 18) else "jump"
        d.cond = BIT(op, 0, 4) != 15
        t = CONDITION[BIT(op, 0, 4)] + d.kind.upper() + " $%04X" % d.target
    elif 0x20 <= top <= 0x27:
        t = CONDITION[BIT(op, 0, 4)] + (_alumac(BIT(op, 18), op) if not BIT(op, 4)
                                         else _aluconst(BIT(op, 18), op) + "  ; 218x only")
    elif 0x28 <= top <= 0x2F:
        if (op & 0x0600FF) == 0x0200AA:
            t = _alumac(2, op) + "  ; 218x only"
        else:
            t = (_alumac(BIT(op, 18), op) + ", " if BIT(op, 13, 5) else "") + "%s = %s" % (
                REG_GRP[0][BIT(op, 4, 4)], REG_GRP[0][BIT(op, 0, 4)])
    elif 0x30 <= top <= 0x3F:
        d.imm_reg, d.imm_val = REG_GRP[BIT(op, 18, 2)][BIT(op, 0, 4)], BIT(op, 4, 14)
        t = "%s = $%04X" % (d.imm_reg, d.imm_val)
    elif 0x40 <= top <= 0x4F:
        d.imm_reg, d.imm_val = REG_GRP[0][BIT(op, 0, 4)], BIT(op, 4, 16)
        t = "%s = $%04X" % (d.imm_reg, d.imm_val)
    elif 0x50 <= top <= 0x5F:
        t = _alumac(BIT(op, 18), op) + ", " if BIT(op, 13, 5) else ""
        r, i, m = REG_GRP[0][BIT(op, 4, 4)], 4 + BIT(op, 2, 2), 4 + BIT(op, 0, 2)
        t += "PM(I%d,M%d) = %s" % (i, m, r) if BIT(op, 19) else "%s = PM(I%d,M%d)" % (r, i, m)
    elif 0x60 <= top <= 0x7F:
        t = _alumac(BIT(op, 18), op) + ", " if BIT(op, 13, 5) else ""
        b = 4 if BIT(op, 20) else 0
        r, i, m = REG_GRP[0][BIT(op, 4, 4)], b + BIT(op, 2, 2), b + BIT(op, 0, 2)
        d.ireg, d.mreg, d.dm_ind_write = i, m, bool(BIT(op, 19))
        t += "DM(I%d,M%d) = %s" % (i, m, r) if BIT(op, 19) else "%s = DM(I%d,M%d)" % (r, i, m)
    elif 0x80 <= top <= 0x9F:
        r, a = REG_GRP[BIT(op, 18, 2)][BIT(op, 0, 4)], BIT(op, 4, 14)
        d.dm_abs, d.dm_write = a, bool(BIT(op, 20))
        t = "DM($%04X) = %s" % (a, r) if d.dm_write else "%s = DM($%04X)" % (r, a)
    elif 0xA0 <= top <= 0xBF:
        b = 4 if BIT(op, 20) else 0
        i, m = b + BIT(op, 2, 2), b + BIT(op, 0, 2)
        d.ireg, d.mreg, d.dm_ind_write = i, m, True
        t = "DM(I%d,M%d) = $%04X" % (i, m, BIT(op, 4, 16))
    else:
        t = (_alumac(0, op) + ", " if BIT(op, 13, 5) else "") + "%s = DM(I%d,M%d), %s = PM(I%d,M%d)" % (
            DUAL_XREG[BIT(op, 18, 2)], BIT(op, 2, 2), BIT(op, 0, 2),
            DUAL_YREG[BIT(op, 20, 2)], 4 + BIT(op, 6, 2), 4 + BIT(op, 4, 2))
        d.ireg, d.mreg = BIT(op, 2, 2), BIT(op, 0, 2)
    d.text = t
    return d


# ---------------------------------------------------------------- analysis
def m_seed(words):
    """M-register values left by a page (last immediate load wins).

    A BFORCE soft reboot reloads PM but does not clear the DAG registers, so a later
    page may rely on M values set by the page that rebooted into it (page 0 here).
    """
    m = {}
    for w in words:
        d = decode(w)
        if d.imm_reg and d.imm_reg[0] == "M" and d.imm_reg[1:].isdigit():
            v = d.imm_val
            m[int(d.imm_reg[1:])] = v - 0x4000 if v & 0x2000 else v
    return m


def analyse(words, seed=None):
    """Decode a page and propagate I/M-register immediates along straight-line code.

    Tracking is reset at every branch target and after unconditional flow changes. Inside
    DO loops only the first iteration's address is shown.
    """
    insns = [decode(w, a) for a, w in enumerate(words)]
    labels = {}
    for d in insns:
        if d.target is not None and d.kind in ("jump", "call"):
            labels.setdefault(d.target, ("sub_%04X" if d.kind == "call" else "loc_%04X") % d.target)
    ival, mval = {}, dict(seed or {})
    cntr = None
    loops = {}                  # body start -> (end, count)
    for d in insns:
        if d.addr in labels:
            ival, mval, cntr = {}, dict(seed or {}), None
        reps = 1
        for start, (end, n) in loops.items():
            if start == d.addr == end and n:
                reps = n
        if d.ireg is not None:
            if d.ireg in ival:
                d.eff = ival[d.ireg]
                if d.mreg in mval:
                    step = mval[d.mreg]
                    if reps > 1:
                        d.rep = (reps, (d.eff + step * (reps - 1)) & 0x3FFF)
                    ival[d.ireg] = (ival[d.ireg] + step * reps) & 0x3FFF
                else:
                    del ival[d.ireg]
        if d.kind == "do":
            loops[d.addr + 1] = (d.target, cntr if d.text.endswith("CE") else None)
        if d.imm_reg == "CNTR":
            cntr = d.imm_val
        if d.imm_reg and d.imm_reg[0] in "IM" and d.imm_reg[1:].isdigit():
            n = int(d.imm_reg[1:])
            v = d.imm_val
            if d.imm_reg[0] == "I":
                ival[n] = v
            else:
                mval[n] = v - 0x4000 if v & 0x2000 else v   # M registers are signed 14-bit
        elif d.text.startswith(("I", "M")) and " = " in d.text and d.imm_reg is None:
            r = d.text.split(" = ")[0]                       # register-to-register move: unknown now
            if r[1:].isdigit():
                (ival if r[0] == "I" else mval).pop(int(r[1:]), None)
        for start, (end, n) in list(loops.items()):
            if d.addr == end:
                if end != start:
                    for b in insns[start:end + 1]:
                        if b.ireg is not None:
                            ival.pop(b.ireg, None)
                del loops[start]
        if d.text.startswith("MODIFY"):
            i = int(d.text[9]); ival.pop(i, None)
        if d.kind in ("jump", "rts", "rti", "ijump") and not d.cond:
            ival, mval = {}, dict(seed or {})
    return insns, labels


def comment(d):
    c = []
    if d.dm_abs is not None:
        c.append(dm_name(d.dm_abs) or dm_region(d.dm_abs))
    if d.eff is not None:
        if d.rep:
            c.append("I%d=$%04X..$%04X x%d %s" % (d.ireg, d.eff, d.rep[1], d.rep[0], dm_name(d.eff) or dm_region(d.eff)))
        else:
            c.append("I%d=$%04X %s" % (d.ireg, d.eff, dm_name(d.eff) or dm_region(d.eff)))
    if d.imm_reg and d.imm_reg[0] == "I" and d.imm_val in CTRL_REGS:
        c.append(CTRL_REGS[d.imm_val])
    return "; " + ", ".join(c) if c else ""


def disassemble(words, page, out, seed=None):
    insns, labels = analyse(words, seed)
    out.write("; ---- boot page %d: %d words loaded at PM $0000 ----\n" % (page, len(words)))
    if seed:
        out.write("; assumed at entry (left by page 0): %s\n" % ", ".join(
            "M%d=%d" % (k, v) for k, v in sorted(seed.items())))
    for d in insns:
        if d.addr in VECTORS:
            out.write("  ; -- vector slot %s --\n" % VECTORS[d.addr])
        if d.addr in labels:
            out.write("\n%s:\n" % labels[d.addr])
        text = d.text
        if d.target is not None and d.target in labels and d.kind in ("jump", "call"):
            text = text.replace("$%04X" % d.target, labels[d.target])
        out.write("  %04X: %06X  %-44s%s\n" % (d.addr, d.op, text, comment(d)))


def xref(words, page, out, seed=None):
    insns, labels = analyse(words, seed)
    abs_acc = collections.defaultdict(lambda: [0, 0, []])
    ind_acc = collections.defaultdict(lambda: [0, 0, []])
    flags, calls = [], collections.Counter()
    for d in insns:
        if d.dm_abs is not None:
            e = abs_acc[d.dm_abs]
            e[1 if d.dm_write else 0] += 1
            e[2].append(d.addr)
        if d.eff is not None:
            e = ind_acc[d.eff]
            e[1 if d.dm_ind_write else 0] += 1
            e[2].append(d.addr)
        if d.flags:
            flags.append((d.addr, d.text))
        if d.kind == "call" and d.target is not None:
            calls[d.target] += 1
    out.write("## Boot page %d (%d words)\n\n" % (page, len(words)))
    out.write("### Direct DM accesses `DM($addr)`\n\n| addr | region / name | reads | writes | at PM |\n|---|---|---|---|---|\n")
    for a in sorted(abs_acc):
        r, w, at = abs_acc[a]
        out.write("| `$%04X` | %s | %d | %d | %s |\n" % (a, dm_name(a) or dm_region(a), r, w,
                                                     " ".join("%04X" % x for x in at[:8]) + (" …" if len(at) > 8 else "")))
    out.write("\n### Indirect DM accesses with a known I-register value\n\n| addr | region / name | reads | writes | at PM |\n|---|---|---|---|---|\n")
    for a in sorted(ind_acc):
        r, w, at = ind_acc[a]
        out.write("| `$%04X` | %s | %d | %d | %s |\n" % (a, dm_name(a) or dm_region(a), r, w,
                                                     " ".join("%04X" % x for x in at[:8]) + (" …" if len(at) > 8 else "")))
    out.write("\n### Flag-pin changes\n\n")
    for a, t in flags:
        out.write("- `%04X` %s\n" % (a, t))
    out.write("\n### Most-called subroutines\n\n")
    for tgt, n in calls.most_common(15):
        out.write("- `%04X` ×%d\n" % (tgt, n))
    out.write("\n")


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("cmd", choices=("pages", "dis", "xref"))
    ap.add_argument("rom")
    ap.add_argument("-p", "--page", type=int, help="boot page (default: all)")
    ap.add_argument("-o", "--out", help="output file (default: stdout)")
    ap.add_argument("--no-seed", action="store_true",
                    help="do not assume page-0 M register values in later pages")
    a = ap.parse_args(argv)
    rom = open(a.rom, "rb").read()
    pages = boot_pages(rom)
    out = open(a.out, "w") if a.out else sys.stdout
    sel = [a.page] if a.page is not None else sorted(pages)
    if a.cmd == "pages":
        for p in sorted(pages):
            out.write("page %d: EPROM $%05X, %4d words (length byte $%02X)\n"
                      % (p, p * PAGE_STRIDE, len(pages[p]), rom[p * PAGE_STRIDE + 3]))
    for p in sel:
        seed = m_seed(pages[0]) if p and 0 in pages and not a.no_seed else None
        if a.cmd == "dis":
            disassemble(pages[p], p, out, seed)
            out.write("\n")
        elif a.cmd == "xref":
            xref(pages[p], p, out, seed)


if __name__ == "__main__":
    main()
