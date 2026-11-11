#!/bin/sh
# Rebuild the primitive model emu/model/srx611_prim.{step,blend,glb} (needs emu/model/joints.json + cables.json
# from build.sh). env: CQ_PY (CadQuery python, default ~/opt/venv-cadquery/bin/python), BLENDER, TMPDIR, KEEP=1.
set -e
ROOT=$(cd "$(dirname "$0")/../.." && pwd); T=$ROOT/tools/model3d
CQ_PY=${CQ_PY:-$HOME/opt/venv-cadquery/bin/python}
BLENDER=${BLENDER:-$HOME/opt/blender-4.5.4-linux-x64/blender}
W=$(mktemp -d)
"$CQ_PY" "$T/prim_cq.py" "$ROOT/emu/model" "$W"
"$BLENDER" -b --python "$T/build_prim_blend.py" -- "$W" "$ROOT/emu/model"
# scan texture (labels) onto base / link1 / link2; needs emu/model/srx611.blend from build.sh
"$BLENDER" -b "$ROOT/emu/model/srx611_prim.blend" --python "$T/bake_prim_textures.py" -- "$ROOT/emu/model/srx611.blend"
rm -f "$ROOT/emu/model/srx611_prim.blend1"
if [ -n "$KEEP" ]; then echo "work dir: $W"; else rm -rf "$W"; fi
