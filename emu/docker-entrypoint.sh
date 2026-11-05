#!/bin/sh
# Run the SRX-C61 emulator.  Any arguments override the default (headless) run.
exec /usr/local/bin/srx-c61 -rompath /roms "$@"
