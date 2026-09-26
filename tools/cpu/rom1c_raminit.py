#!/usr/bin/env python3
"""Rebuild the initial RAM image of the SRX-611 CPU firmware (ROM1-C.bin).

At boot, `reset_entry` calls 0x5308, which walks a record stream in ROM (file offset
0xCE695 .. 0xD9D94) and copies initialised data into RAM. Nearly all strings (menus, TP
texts, the E000..E401 messages) and the pointer tables that index them live in that stream,
so the code references their *RAM* addresses (e.g. the error-message table at RAM 0x26F4),
not ROM addresses. That is why IDA shows no string xrefs.

Record format (first byte = type):
  0                                end of stream
  1  sel16                         segment selector (ignored here)
  2  addr32 len16 data[len]        copy
  3  addr32 count32 len32 pat[len] fill: repeat pat `count` times
  4  addr16 len16 data[len]        copy (short address)
  5  addr16 count16 len16 pat[len] fill (short address)

Usage:
  python3 tools/cpu/rom1c_raminit.py [ROM1-C.bin] [-o ram.bin] [--find TEXT] [--ptr ADDR]
    -o      write the RAM image (0 .. highest initialised byte)
    --find  print the RAM address(es) of a string
    --ptr   list RAM dwords that point to ADDR (finds pointer tables)
"""
import argparse
import re
import struct

STREAM = 0xCE695


def build(rom):
    ram = bytearray(0x10000)
    p, hi, n = STREAM, 0, 0
    while True:
        t = rom[p]
        if t == 0:
            break
        if t == 1:
            p += 3
            continue
        if t == 2:
            a, ln = struct.unpack_from('<IH', rom, p + 1)
            data, p = rom[p + 7:p + 7 + ln], p + 7 + ln
        elif t == 3:
            a, c, ln = struct.unpack_from('<III', rom, p + 1)
            data, p = rom[p + 13:p + 13 + ln] * c, p + 13 + ln
        elif t == 4:
            a, ln = struct.unpack_from('<HH', rom, p + 1)
            data, p = rom[p + 5:p + 5 + ln], p + 5 + ln
        elif t == 5:
            a, c, ln = struct.unpack_from('<HHH', rom, p + 1)
            data, p = rom[p + 7:p + 7 + ln] * c, p + 7 + ln
        else:
            raise ValueError('unknown record type %d at 0x%X' % (t, p))
        if a + len(data) > len(ram):
            ram.extend(bytes(a + len(data) - len(ram)))
        ram[a:a + len(data)] = data
        hi, n = max(hi, a + len(data)), n + 1
    return bytes(ram[:hi]), n, p


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('rom', nargs='?', default='FW/SRX6-CPU/2/ROM1-C.bin')
    ap.add_argument('-o', '--out')
    ap.add_argument('--find')
    ap.add_argument('--ptr', type=lambda s: int(s, 0))
    a = ap.parse_args()
    ram, n, end = build(open(a.rom, 'rb').read())
    print('%d records, stream end 0x%X, RAM image 0x0..0x%X' % (n, end, len(ram)))
    if a.out:
        open(a.out, 'wb').write(ram)
    if a.find:
        for m in re.finditer(re.escape(a.find.encode('latin1')), ram):
            print('"%s" at RAM 0x%X' % (a.find, m.start()))
    if a.ptr is not None:
        for m in re.finditer(re.escape(struct.pack('<I', a.ptr)), ram):
            print('pointer to 0x%X at RAM 0x%X' % (a.ptr, m.start()))


if __name__ == '__main__':
    main()
