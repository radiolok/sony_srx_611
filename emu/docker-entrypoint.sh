#!/bin/sh
# Run the SRX-C61 emulator.  Any arguments override the default (headless) run.
# NVRAM (the parameter EEPROM) lives in /nvram; mount a host directory there
# to keep it between runs:
#   docker run --user "$(id -u):$(id -g)" -v "$PWD/nvram:/nvram" ...
mkdir -p /nvram
exec /usr/local/bin/srx-c61 -rompath /roms -nvram_directory /nvram "$@"
