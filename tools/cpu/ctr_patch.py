#!/usr/bin/env python3
"""Patch an SRX-611 parameter EEPROM image (.CTR block) for another arm.

The 8 KB EEPROM holds the .CTR block (RAM 0x4A24-0x622C, 0x1809 bytes) at offset 0.
The firmware keeps no checksum over it (doc/robot_parameters.md §4.3), so changing a
field is enough. Only the per-arm calibration is changed:

    0x100 / 0x108                double   ARM LENGTH L1 / L2 (mm)
    0x188 / 0x194 / 0x1A0 / 0x1AC int32    HOME PARA theta1 / theta2 / Z / R (counts)
    0x004 / 0x020                char[8]  controller number (optional, --serial)

Example (owner's arm, R.No. 82912 / C61-1173):
    ctr_patch.py FW/SRX6-CPU/1/U50_AT28C64@SOIC28.bin out.bin \
        --l1 349.847 --l2 249.699 --home 200868 173395 18950 0 --serial C61-1173
"""
import argparse
import struct
import sys

BLOCK_LEN = 0x1809
L1, L2 = 0x100, 0x108
HOME = (0x188, 0x194, 0x1A0, 0x1AC)
SERIAL = (0x04, 0x20)


def show(img, tag):
    l1, = struct.unpack_from("<d", img, L1)
    l2, = struct.unpack_from("<d", img, L2)
    home = [struct.unpack_from("<i", img, o)[0] for o in HOME]
    ser = bytes(img[SERIAL[0]:SERIAL[0] + 8]).rstrip(b"\0 ").decode("ascii", "replace")
    print(f"{tag}: serial {ser}  L1 {l1:.3f}  L2 {l2:.3f}  HOME {home}")


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("src")
    ap.add_argument("dst")
    ap.add_argument("--l1", type=float, required=True)
    ap.add_argument("--l2", type=float, required=True)
    ap.add_argument("--home", type=int, nargs=4, required=True, metavar=("T1", "T2", "Z", "R"))
    ap.add_argument("--serial", help="controller number, max 8 chars (e.g. C61-1173)")
    a = ap.parse_args()

    img = bytearray(open(a.src, "rb").read())
    if len(img) != 8192:
        sys.exit(f"{a.src}: expected 8192 bytes, got {len(img)}")
    size, = struct.unpack_from("<H", img, 2)
    if img[0] != 0x5B or size != BLOCK_LEN or img[BLOCK_LEN - 1] != 0xED:
        sys.exit(f"{a.src}: not a .CTR block (kind {img[0]:02X}, size {size:#x}, "
                 f"end {img[BLOCK_LEN - 1]:02X}); blank or misread dump?")

    show(img, "before")
    struct.pack_into("<d", img, L1, a.l1)
    struct.pack_into("<d", img, L2, a.l2)
    for off, v in zip(HOME, a.home):
        struct.pack_into("<i", img, off, v)
    if a.serial:
        s = a.serial.encode("ascii")
        if len(s) > 8:
            sys.exit("--serial: max 8 characters")
        for off in SERIAL:
            img[off:off + 8] = s.ljust(8, b" ")  # the firmware pads with spaces (0xAB1A)
    show(img, "after ")
    open(a.dst, "wb").write(img)


if __name__ == "__main__":
    main()
