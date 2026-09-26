#!/usr/bin/env python3
"""Dump the LUNA keyword/symbol table embedded in SRXWIN/LUNNA.EXE (LUNA 5.0 compiler v1.05).

The table is alphabetically sorted, 15-byte records: name[9] (NUL-padded) + d0..d5.
Usage: lunna_symtab.py LUNNA.EXE [--md]
"""
import re, sys

REC = 15


def symtab(path):
    d = open(path, 'rb').read()
    anchor = d.find(b'TRCKCHERR\0')
    assert anchor > 0, 'anchor keyword not found'

    def ok(p):
        name = d[p:p + 9].rstrip(b'\0')
        return 0x41 <= d[p] <= 0x5A and re.fullmatch(rb'[A-Z][A-Z0-9!]*', name) is not None \
            and b'\0' not in name

    s = anchor
    while ok(s - REC): s -= REC
    e = anchor
    while ok(e + REC): e += REC
    return s, [(d[p:p + 9].split(b'\0')[0].decode(), d[p + 9:p + REC]) for p in range(s, e + REC, REC)]


if __name__ == '__main__':
    start, rows = symtab(sys.argv[1])
    if '--md' in sys.argv:
        print('| Keyword | d0 args | d1 class | d2 code | d3 group | d4d5 (LE word) |')
        print('|---|---|---|---|---|---|')
        for n, b in rows:
            print('| `%s` | %02X | %02X | %02X | %02X | %04X |' % (n, b[0], b[1], b[2], b[3], b[4] | b[5] << 8))
    else:
        print('# LUNNA.EXE symbol table @file 0x%X, %d records' % (start, len(rows)))
        for n, b in rows: print('%-9s %s' % (n, b.hex(' ')))
