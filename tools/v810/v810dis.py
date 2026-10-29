#!/usr/bin/env python3
"""NEC V810 (uPD70732) linear disassembler with constant tracking — SRX6-SERVO firmware.

`FW/SRX6-SERVO/ROM_SERVO.bin` (256 KB) is mapped at 0x00100000 (file offset 0); the
reset vector at file 0x3FFF0 (CPU address 0xFFFFFFF0) does `movhi 0x10,r0,r31; jmp [r31]`.

Encoding (little-endian halfwords; opcode = bits 15..10 of the first halfword):
  I   op reg2 reg1                 16-bit   register ops
  II  op reg2 imm5                 16-bit   imm5 ops, SETF, LDSR/STSR, TRAP, RETI, HALT, BSTR
  III 100 cond(4) disp9            16-bit   Bcond
  IV  op disp26                    32-bit   JR, JAL
  V   op reg2 reg1 | imm16         32-bit   MOVEA, ADDI, MOVHI, ORI, ANDI, XORI
  VI  op reg2 reg1 | disp16        32-bit   LD/ST/IN/OUT/CAXI
  VII op reg2 reg1 | subop ...     32-bit   FPU / extended
  Opcodes >= 0b101000 are 32-bit, the rest 16-bit.

Constant tracking: registers loaded by MOVHI/MOVEA/ADDI/ORI/MOV imm5 (and copies) are
followed along straight-line code; tracking resets at branch targets and after
unconditional jumps. Loads/stores through a known base get their absolute address in the
comment, so peripheral and shared-memory accesses can be found.

Usage:
  v810dis.py dis   ROM [--base 0x100000] [--start A] [--end A] [-o FILE]
  v810dis.py refs  ROM ADDR_LO ADDR_HI [--base ...]   # code touching that address range
  v810dis.py imm   ROM VALUE [VALUE ...]               # instructions using an immediate
  v810dis.py consts ROM [LO HI]                        # address constants (movhi+movea/disp)
"""
import argparse
import sys

REG = ["r0"] + ["r%d" % i for i in range(1, 32)]
REG[2], REG[3], REG[4], REG[5], REG[31] = "fp", "sp", "gp", "tp", "lp"
COND = ["v", "c", "z", "nh", "n", "r", "lt", "le", "nv", "nc", "nz", "h", "p", "nop", "ge", "gt"]
SREG = {0: "EIPC", 1: "EIPSW", 2: "FEPC", 3: "FEPSW", 4: "ECR", 5: "PSW", 6: "PIR", 7: "TKCW",
        24: "CHCW", 25: "ADTRE"}
OPS16_I = {0x00: "mov", 0x01: "add", 0x02: "sub", 0x03: "cmp", 0x04: "shl", 0x05: "shr",
           0x07: "sar", 0x08: "mul", 0x09: "div", 0x0A: "mulu", 0x0B: "divu", 0x0C: "or",
           0x0D: "and", 0x0E: "xor", 0x0F: "not"}
OPS16_II = {0x10: "mov", 0x11: "add", 0x13: "cmp", 0x14: "shl", 0x15: "shr", 0x17: "sar"}
OPS32_V = {0x28: "movea", 0x29: "addi", 0x2C: "ori", 0x2D: "andi", 0x2E: "xori", 0x2F: "movhi"}
OPS32_VI = {0x30: ("ld.b", 1, False), 0x31: ("ld.h", 2, False), 0x33: ("ld.w", 4, False),
            0x34: ("st.b", 1, True), 0x35: ("st.h", 2, True), 0x37: ("st.w", 4, True),
            0x38: ("in.b", 1, False), 0x39: ("in.h", 2, False), 0x3B: ("in.w", 4, False),
            0x3C: ("out.b", 1, True), 0x3D: ("out.h", 2, True), 0x3F: ("out.w", 4, True),
            0x3A: ("caxi", 4, True)}
BSTR = {0: "sch0bsu", 1: "sch0bsd", 2: "sch1bsu", 3: "sch1bsd", 8: "orbsu", 9: "andbsu",
        10: "xorbsu", 11: "movbsu", 12: "ornbsu", 13: "andnbsu", 14: "xornbsu", 15: "notbsu"}
FPU = {0: "cmpf.s", 2: "cvt.ws", 3: "cvt.sw", 4: "addf.s", 5: "subf.s", 6: "mulf.s", 7: "divf.s",
       11: "trnc.sw"}


def sx(v, bits):
    return v - (1 << bits) if v & (1 << (bits - 1)) else v


class Ins:
    __slots__ = ("addr", "size", "text", "op", "r1", "r2", "imm", "target", "kind", "mem", "store", "msize")

    def __init__(self, addr):
        self.addr, self.size = addr, 2
        self.text, self.op = "", None
        self.r1 = self.r2 = self.imm = self.target = self.kind = None
        self.mem = None       # (base reg, disp) for LD/ST/IN/OUT
        self.store = False
        self.msize = 0


def decode(buf, off, addr):
    d = Ins(addr)
    if off + 2 > len(buf):
        d.text = ".half ?"
        return d
    hw = buf[off] | buf[off + 1] << 8
    op = hw >> 10
    r2, r1 = (hw >> 5) & 31, hw & 31
    d.op, d.r1, d.r2 = op, r1, r2
    if op >> 3 == 0b100:                              # Bcond
        c = (hw >> 9) & 15
        disp = sx(hw & 0x1FF, 9)
        d.target = (addr + disp) & 0xFFFFFFFF
        d.kind = "br" if c == 5 else ("nop" if c == 13 else "bcond")
        d.text = "nop" if c == 13 else "b%-6s 0x%08X" % (COND[c], d.target)
        return d
    if op >= 0x28:
        d.size = 4
        if off + 4 > len(buf):
            d.text = ".half 0x%04X" % hw
            d.size = 2
            return d
        lo = buf[off + 2] | buf[off + 3] << 8
        if op in (0x2A, 0x2B):                        # JR / JAL
            disp = sx(((hw & 0x3FF) << 16) | lo, 26)
            d.target = (addr + disp) & 0xFFFFFFFF
            d.kind = "jr" if op == 0x2A else "jal"
            d.text = "%-7s 0x%08X" % (d.kind, d.target)
        elif op in OPS32_V:
            d.imm = lo
            n = OPS32_V[op]
            if n in ("movea", "addi"):
                d.text = "%-7s %s, %s, %s" % (n, hex(sx(lo, 16)), REG[r1], REG[r2])
            else:
                d.text = "%-7s 0x%04X, %s, %s" % (n, lo, REG[r1], REG[r2])
        elif op in OPS32_VI:
            n, sz, st = OPS32_VI[op]
            disp = sx(lo, 16)
            d.mem, d.store, d.msize = (r1, disp), st, sz
            if st:
                d.text = "%-7s %s, %s[%s]" % (n, REG[r2], hex(disp), REG[r1])
            else:
                d.text = "%-7s %s[%s], %s" % (n, hex(disp), REG[r1], REG[r2])
        elif op == 0x3E:
            sub = lo >> 10
            d.text = "%-7s %s, %s" % (FPU.get(sub, "ext.%02X" % sub), REG[r1], REG[r2])
        else:
            d.text = ".word  0x%04X%04X  ; op %02X" % (lo, hw, op)
        return d
    if op in OPS16_I:
        d.text = "%-7s %s, %s" % (OPS16_I[op], REG[r1], REG[r2])
    elif op == 0x06:
        d.kind = "jmp"
        d.text = "jmp     [%s]" % REG[r1]
    elif op in OPS16_II:
        imm = sx(r1, 5) if op in (0x10, 0x11, 0x13) else r1
        d.imm = imm
        d.text = "%-7s %d, %s" % (OPS16_II[op], imm, REG[r2])
    elif op == 0x12:
        d.text = "setf    %s, %s" % (COND[r1 & 15], REG[r2])
    elif op == 0x18:
        d.text = "trap    %d" % r1
    elif op == 0x19:
        d.kind = "reti"
        d.text = "reti"
    elif op == 0x1A:
        d.text = "halt"
    elif op == 0x1C:
        d.text = "ldsr    %s, %s" % (REG[r2], SREG.get(r1, "sr%d" % r1))
    elif op == 0x1D:
        d.text = "stsr    %s, %s" % (SREG.get(r1, "sr%d" % r1), REG[r2])
    elif op == 0x1F:
        d.text = BSTR.get(r1, "bstr.%d" % r1)
    else:
        d.text = ".half  0x%04X  ; op %02X" % (hw, op)
    return d


def sweep(buf, base, start=None, end=None):
    """Linear sweep; returns list of Ins."""
    a = (start if start is not None else base)
    stop = end if end is not None else base + len(buf)
    out = []
    while a < stop:
        d = decode(buf, a - base, a)
        out.append(d)
        a += d.size
    return out


def track(insns, seed=None):
    """Attach absolute addresses to memory accesses where the base register is known.

    `seed` = {reg: value} for registers fixed for the whole program (e.g. gp); they are
    restored whenever tracking resets.
    """
    seed = dict(seed or {})
    targets = {d.target for d in insns if d.target is not None}
    regs = dict(seed)
    res = {}
    for d in insns:
        if d.addr in targets:
            regs = dict(seed)
        regs[0] = 0
        eff = None
        if d.mem is not None:
            b, disp = d.mem
            if b in regs:
                eff = (regs[b] + disp) & 0xFFFFFFFF
                res[d.addr] = eff
        op = d.op
        if op is not None and d.size == 4 and d.imm is not None:
            v = d.imm
            if op == 0x2F and d.r1 in regs:       # movhi
                regs[d.r2] = (regs[d.r1] + (v << 16)) & 0xFFFFFFFF
            elif op in (0x28, 0x29) and d.r1 in regs:
                regs[d.r2] = (regs[d.r1] + sx(v, 16)) & 0xFFFFFFFF
            elif op == 0x2C and d.r1 in regs:
                regs[d.r2] = regs[d.r1] | v
            elif op == 0x2D and d.r1 in regs:
                regs[d.r2] = regs[d.r1] & v
            elif op == 0x2E and d.r1 in regs:
                regs[d.r2] = regs[d.r1] ^ v
            else:
                regs.pop(d.r2, None)
        elif op == 0x10:                          # mov imm5
            regs[d.r2] = d.imm & 0xFFFFFFFF
        elif op == 0x00 and d.size == 2 and d.kind is None:   # mov reg
            if d.r1 in regs:
                regs[d.r2] = regs[d.r1]
            else:
                regs.pop(d.r2, None)
        elif op == 0x11 and d.r2 in regs:         # add imm5
            regs[d.r2] = (regs[d.r2] + d.imm) & 0xFFFFFFFF
        elif op is not None and d.mem is not None and not d.store:
            regs.pop(d.r2, None)
        elif op is not None and ((d.size == 2 and op in OPS16_I) or op in (0x14, 0x15, 0x17, 0x1D, 0x12)):
            regs.pop(d.r2, None)
        if d.kind in ("jal",):
            for r in list(regs):
                if r in (10, 30, 31) or 6 <= r <= 19:  # caller-saved per NEC conventions (approx.)
                    regs.pop(r, None)
        if d.kind in ("jr", "jmp", "reti", "br"):
            regs = dict(seed)
    return res


def consts(insns):
    """Flow-insensitive address constants: `movhi H,r0,rX` followed (within 8 insns,
    rX not redefined) by `movea/addi L,rX,rY` or a load/store `disp[rX]`.
    Returns [(insn addr, constant, use)] — catches values merged at branch targets
    that `track` drops."""
    out = []
    for i, d in enumerate(insns):
        if d.op != 0x2F or d.r1 != 0 or d.imm is None:
            continue
        hi, rx = d.imm << 16, d.r2
        for e in insns[i + 1:i + 9]:
            if e.mem is not None and e.mem[0] == rx:
                out.append((e.addr, (hi + e.mem[1]) & 0xFFFFFFFF, e.text.split()[0]))
            elif e.op in (0x28, 0x29) and e.r1 == rx and e.size == 4:
                v = (hi + sx(e.imm, 16)) & 0xFFFFFFFF
                out.append((e.addr, v, "addr"))
                # follow one level: uses of rY with displacement
                ry = e.r2
                j = insns.index(e)
                for f in insns[j + 1:j + 7]:
                    if f.mem is not None and f.mem[0] == ry:
                        out.append((f.addr, (v + f.mem[1]) & 0xFFFFFFFF, f.text.split()[0]))
                    if f.r2 == ry and f.mem is None and f.kind is None and f.op not in (0x03, 0x13):
                        break
                if ry == rx:
                    break
            if e.r2 == rx and e.kind is None and e.op not in (0x03, 0x13) and not (e.mem and e.store):
                if not (e.op in (0x28, 0x29) and e.r1 == rx):
                    break
            if e.kind in ("jr", "jmp", "reti"):
                break
    return out


def fmt(d, eff=None, labels=None):
    t = d.text
    if labels and d.target in labels:
        t = t.replace("0x%08X" % d.target, labels[d.target])
    c = "; [0x%08X]" % eff if eff is not None else ""
    return "  %08X: %-44s%s" % (d.addr, t, c)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("cmd", choices=("dis", "refs", "imm", "consts"))
    ap.add_argument("rom")
    ap.add_argument("args", nargs="*")
    ap.add_argument("--base", type=lambda s: int(s, 0), default=0x100000)
    ap.add_argument("--start", type=lambda s: int(s, 0))
    ap.add_argument("--end", type=lambda s: int(s, 0))
    ap.add_argument("--ctx", type=int, default=0, help="refs/imm: instructions of context before")
    ap.add_argument("--seed", action="append", default=[],
                    help="REG=VALUE known for the whole program, e.g. gp=0x2BAEC (repeatable)")
    ap.add_argument("-o", "--out")
    a = ap.parse_args(argv)
    buf = open(a.rom, "rb").read()
    out = open(a.out, "w") if a.out else sys.stdout
    ins = sweep(buf, a.base, a.start, a.end)
    seed = {}
    for kv in a.seed:
        r, v = kv.split("=")
        seed[REG.index(r) if r in REG else int(r.lstrip("r"))] = int(v, 0)
    eff = track(ins, seed)
    labels = {}
    for d in ins:
        if d.target is not None and d.kind in ("jal",):
            labels[d.target] = "sub_%08X" % d.target
    idx = {d.addr: i for i, d in enumerate(ins)}
    if a.cmd == "dis":
        for d in ins:
            if d.addr in labels:
                out.write("\n%s:\n" % labels[d.addr])
            out.write(fmt(d, eff.get(d.addr), labels) + "\n")
    elif a.cmd == "refs":
        lo, hi = int(a.args[0], 0), int(a.args[1], 0)
        for addr, e in sorted(eff.items()):
            if lo <= e <= hi:
                i = idx[addr]
                for k in range(max(0, i - a.ctx), i):
                    out.write(fmt(ins[k], eff.get(ins[k].addr)) + "\n")
                out.write(fmt(ins[i], e) + ("\n---\n" if a.ctx else "\n"))
    elif a.cmd == "consts":
        lo = int(a.args[0], 0) if a.args else 0
        hi = int(a.args[1], 0) if len(a.args) > 1 else 0xFFFFFFFF
        seen = {}
        for addr, v, use in consts(ins):
            if lo <= v <= hi:
                seen.setdefault(addr, (v, use))
        for addr, e in eff.items():
            if lo <= e <= hi and addr not in seen:
                seen[addr] = (e, ins[idx[addr]].text.split()[0])
        for addr in sorted(seen):
            v, use = seen[addr]
            out.write("%08X  0x%08X  %s\n" % (addr, v, use))
    elif a.cmd == "imm":
        vals = {int(v, 0) & 0xFFFF for v in a.args}
        for i, d in enumerate(ins):
            if d.imm is not None and (d.imm & 0xFFFF) in vals and d.size == 4:
                for k in range(max(0, i - a.ctx), i):
                    out.write(fmt(ins[k], eff.get(ins[k].addr)) + "\n")
                out.write(fmt(d, eff.get(d.addr)) + ("\n---\n" if a.ctx else "\n"))


if __name__ == "__main__":
    main()
