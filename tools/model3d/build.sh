#!/bin/sh
# Rebuild emu/model/srx611.{blend,glb} from the 3dScannerApp scan zip.
# usage: tools/model3d/build.sh [scan.zip]   (env: KEEP=1 keeps the work dir, TMPDIR picks where it goes)   (needs python3+numpy+Pillow, Blender 4.5 at $BLENDER)
set -e
ROOT=$(cd "$(dirname "$0")/../.." && pwd); T=$ROOT/tools/model3d
ZIP=${1:-$ROOT/emu/model/scan/Untitled_Scan_11_28_02.zip}
BLENDER=${BLENDER:-$HOME/opt/blender-4.5.4-linux-x64/blender}
W=$(mktemp -d); mkdir "$W/scan"; unzip -q "$ZIP" -d "$W/scan"
python3 -I "$T/dae_to_npz.py" "$W"/scan/*.dae "$W/mesh.npz"
python3 -I "$T/segment.py" "$W/mesh.npz" "$W/seg" "$W/scan/textured_output.jpg"
cp "$W/seg/joints.json" "$W/seg/cables.json" "$ROOT/emu/model/"
"$BLENDER" -b --python "$T/build_blend.py" -- "$W/seg" "$ROOT/emu/model"
rm -f "$ROOT/emu/model/srx611.blend1"
[ -n "$PREVIEW" ] && python3 -I "$T/labrender.py" "$W/mesh.npz" "$W/seg/labels.npy" "$W/scan/textured_output.jpg" "$PREVIEW"
if [ -n "$KEEP" ]; then echo "work dir: $W"; else rm -rf "$W"; fi
