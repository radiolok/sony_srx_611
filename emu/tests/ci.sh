#!/bin/sh
# Smoke tests for the SRX-C61 emulator image (used by CI, runnable locally).
#
#   emu/tests/ci.sh [image]        # default image: srx-c61-emu
#
# Each test runs the container headless with a fresh NVRAM directory and
# checks the output for its PASS marker.
set -u

IMAGE="${1:-srx-c61-emu}"
TESTS="$(cd "$(dirname "$0")" && pwd)"
WORK="$(mktemp -d)"
trap 'rm -rf "$WORK"' EXIT
FAILED=0

run() {   # run <name> <nvram dir> <mame args...>
	name=$1; nv=$2; shift 2
	mkdir -p "$nv"
	docker run --rm --user "$(id -u):$(id -g)" \
		-v "$nv:/nvram" -v "$TESTS:/tests:ro" \
		"$IMAGE" srx_c61 -video none -sound none -nothrottle "$@" \
		> "$WORK/$name.log" 2>&1
	echo "--- $name (exit $?)"
	grep -E "tp_keys:|eeprom:|servo_cycle:|SRX TP: handshake|EEPROM:" "$WORK/$name.log" || true
}

check() { # check <name> <pattern>
	if grep -q "$2" "$WORK/$1.log"; then
		echo "ok   $1: $2"
	else
		echo "FAIL $1: missing '$2'"; FAILED=1
		tail -40 "$WORK/$1.log"
	fi
}

# 1. Boot + pendant: handshake between the real CPU and TP firmwares, and a
#    key press handled after 15 s (Z180 ASCI regression).
run boot "$WORK/nv_boot" -seconds_to_run 30 -oslog -autoboot_script /tests/tp_keys.lua
check boot "SRX TP: handshake PASSED"
check boot "tp_keys: PASS"

# 2. EEPROM persistence: first run writes a pattern, second run finds it.
run eeprom1 "$WORK/nv_eeprom" -seconds_to_run 3 -autoboot_script /tests/eeprom_nvram.lua
check eeprom1 "eeprom: pattern written"
run eeprom2 "$WORK/nv_eeprom" -seconds_to_run 3 -autoboot_script /tests/eeprom_nvram.lua
check eeprom2 "eeprom: PASS"

# 3. Servo cycle with a real .CTR block (unit-1 U50 dump patched for arm
#    82912): V810 link state 2, level-14 cycle running, no E050/E030.
REPO="$(cd "$TESTS/../.." && pwd)"
mkdir -p "$WORK/nv_cycle/srx_c61"
python3 "$REPO/tools/cpu/ctr_patch.py" "$REPO/FW/SRX6-CPU/1/U50_AT28C64@SOIC28.bin" \
	"$WORK/nv_cycle/srx_c61/eeprom_nv" --l1 349.847 --l2 249.699 \
	--home 200868 173395 18950 0 > /dev/null
run cycle "$WORK/nv_cycle" -seconds_to_run 20 -autoboot_script /tests/servo_cycle.lua
check cycle "servo_cycle: PASS"

[ "$FAILED" -eq 0 ] && echo "all emulator smoke tests passed"
exit "$FAILED"
