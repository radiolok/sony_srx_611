#!/bin/sh
# Copy the SRX-C61 firmware images from the repository into the MAME ROM set
# emu/roms/srx_c61/.  The firmware lives under FW/ at the repo root; this
# script produces the flattened ROM names that the driver declares.
set -eu

REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
EMU_DIR="$(cd "$(dirname "$0")" && pwd)"
DST="$EMU_DIR/roms/srx_c61"

mkdir -p "$DST"

cp "$REPO_ROOT/FW/SRX6-CPU/2/ROM1-C.bin"               "$DST/rom1_c.bin"
cp "$REPO_ROOT/FW/SRX6-CPU/2/U23_M27C256B@DIP28.BIN"   "$DST/u23_eprom.bin"
cp "$REPO_ROOT/FW/SRX6-SERVO/ROM_SERVO.bin"             "$DST/rom_servo.bin"
cp "$REPO_ROOT/FW/SERVO_IO/1/U7_M27C512@DIP28.BIN"      "$DST/u7_dsp.bin"
cp "$REPO_ROOT/FW/SERVO_IO/1/U18_M27C512@DIP28.BIN"     "$DST/u18_dsp.bin"

echo "ROM set created in $DST"
