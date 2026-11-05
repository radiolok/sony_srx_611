#!/bin/sh
# Build the SRX-C61 MAME driver into a local MAME checkout (host build, no
# Docker).  See doc/emulator_plan.md section 1.
#
#   ./build.sh              # clone MAME (if needed), build, leave binary at $MAME_DIR/mame
#   ./build.sh --docker     # build the Docker image instead (preferred)
#
# The build uses SOURCES= to compile only the srx_c61 driver plus the MAME
# core and the devices it pulls in, which is far faster than a full MAME build.

set -eu

MAME_VERSION="${MAME_VERSION:-mame0289}"
MAME_DIR="${MAME_DIR:-$HOME/opt/mame}"
MAKE_JOBS="${MAKE_JOBS:-$(nproc)}"
EMU_DIR="$(cd "$(dirname "$0")" && pwd)"

case "${1:-}" in
  --docker)
    "$EMU_DIR/make_roms.sh"
    exec docker build -f "$EMU_DIR/Dockerfile" -t srx-c61-emu "$EMU_DIR"
    ;;
esac

# ---- host build ----

if [ ! -f "$MAME_DIR/makefile" ]; then
  echo "Cloning MAME $MAME_VERSION into $MAME_DIR ..."
  git clone --depth 1 --branch "$MAME_VERSION" https://github.com/mamedev/mame.git "$MAME_DIR"
fi

# Install the driver and register it in the driver list.
cp "$EMU_DIR/src/mame/sony/srx_c61.cpp" "$MAME_DIR/src/mame/sony/srx_c61.cpp"
if ! grep -q '@source:sony/srx_c61\.cpp' "$MAME_DIR/src/mame/mame.lst"; then
  sed -i '/^@source:sony\/taitogn\.cpp$/i @source:sony/srx_c61.cpp\nsrx_c61\n' "$MAME_DIR/src/mame/mame.lst"
fi

# ROM set for the run.
"$EMU_DIR/make_roms.sh"
mkdir -p "$MAME_DIR/roms/srx_c61"
cp "$EMU_DIR/roms/srx_c61/"*.bin "$MAME_DIR/roms/srx_c61/"

cd "$MAME_DIR"
make -j"$MAKE_JOBS" \
  SOURCES=src/mame/sony/srx_c61.cpp \
  REGENIE=1 \
  USE_QTDEBUG=0 \
  NO_USE_MIDI=1 NO_USE_PORTAUDIO=1 NO_USE_PULSEAUDIO=1 NO_USE_PIPEWIRE=1

echo
echo "Built $MAME_DIR/mame"
echo "Run:  $MAME_DIR/mame -rompath roms srx_c61 -video none -sound none -nothrottle"
