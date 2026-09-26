#!/usr/bin/env python3
"""List protocol frame builders in SRXWIN/SRXMONIE.EXE (or any SRXWIN DOS tool).

Finds `mov byte [bp-x], 1Bh` (frame start) and records the constant/argument stores that follow
into the same frame: +1 = LEN, +2 = CMD, +3.. = arguments. See doc/SRXWIN_protocol.md §6.
Requires: pip install capstone
Usage: srxmonie_cmds.py SRXMONIE.EXE
"""
import re, sys
import capstone


def disp(op):
    m = re.search(r'\[bp - (0x[0-9a-f]+|\d+)\]', op)
    return -int(m.group(1), 0) if m else None


def scan(path):
    d = open(path, 'rb').read()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_16)
    for x in re.finditer(rb'\xc6(\x86..|\x46.)\x1b', d, re.S):
        a = x.start()
        ins = list(md.disasm(d[a:a + 300], a))
        base = disp(ins[0].op_str); fields = {}; reg = {}
        for i in ins[1:]:
            if i.mnemonic in ('call', 'lcall'): break
            if i.mnemonic != 'mov' or ',' not in i.op_str: continue
            dst, src = [s.strip() for s in i.op_str.split(',', 1)]
            dd = disp(dst)
            if dd is not None and 0 <= dd - base < 0x40:
                w = 'u16' if dst.startswith('word') else 'u8'
                v = int(src, 0) if re.fullmatch(r'0x[0-9a-f]+|\d+', src) else reg.get(src, 'arg')
                fields.setdefault(dd - base, (w, v))
            elif dst in ('al', 'cl', 'ax', 'cx') and re.fullmatch(r'0x[0-9a-f]+|\d+', src):
                reg[dst] = int(src, 0)
            else:
                reg.pop(dst, None)
        yield a, fields


if __name__ == '__main__':
    for a, f in scan(sys.argv[1]):
        cmd = f.get(2, ('', '?'))[1]; ln = f.get(1, ('', '?'))[1]
        args = ' '.join('+%d:%s%s' % (o, w, '' if v == 'arg' else '=%s' % (hex(v) if isinstance(v, int) else v))
                        for o, (w, v) in sorted(f.items()) if o > 2 and (not isinstance(ln, int) or o < ln - 1))
        print('%06X cmd=%-4s len=%-4s %s' % (a, hex(cmd) if isinstance(cmd, int) else cmd,
                                             ln if isinstance(ln, int) else 'var', args))
