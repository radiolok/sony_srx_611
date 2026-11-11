"""Bake the scan texture (labels SONY / SRX etc.) onto the body parts of the primitive model.

blender -b emu/model/srx611_prim.blend --python tools/model3d/bake_prim_textures.py -- <scan.blend> [res]

Both models sit in the scan pose with identical pivots, so the scan link meshes are appended from
<scan.blend> and the diffuse colour is baked "selected to active" onto a Smart-UV-unwrapped copy of
each primitive body part. Texels whose ray misses the scan keep the plain body colour. The scan
objects are removed again. Missed rays (written as exact black) get the body colour. The .blend is saved and srx611_prim.glb re-exported next to it.
"""
import bpy, sys, os, math
import numpy as np
argv = sys.argv[sys.argv.index("--") + 1:]
scan_blend = os.path.abspath(argv[0]); RES = int(argv[1]) if len(argv) > 1 else 2048
PAIRS = {"base": "base", "link1": "link1", "link2": "link2"}   # primitive part <- scan part
BODY = (0.80, 0.78, 0.71, 1.0)
CAGE, RAY = 0.02, 0.04           # primitives deviate from the scan by up to ~2 cm

sc = bpy.context.scene
sc.render.engine = "CYCLES"; sc.cycles.device = "CPU"; sc.cycles.samples = 4
bk = sc.render.bake
bk.use_selected_to_active = True; bk.cage_extrusion = CAGE; bk.max_ray_distance = RAY
bk.use_pass_direct = False; bk.use_pass_indirect = False; bk.use_pass_color = True
bk.margin = 8

# append the scan link meshes (and their joint empties, so the world matrices evaluate)
with bpy.data.libraries.load(scan_blend, link=False) as (src, dst):
    names = [n for n in src.objects if n in PAIRS.values()]
    dst.objects = list(names)   # Blender replaces the list items with Objects
appended = []
for n, o in zip(names, dst.objects):
    o.name = "scan_" + n; appended.append(o)
    p = o
    while p is not None:
        if p.name not in sc.collection.objects: sc.collection.objects.link(p)
        if p not in appended: appended.append(p)
        p = p.parent
bpy.context.view_layer.update()

for prim, scan in PAIRS.items():
    t = bpy.data.objects[prim]; s = bpy.data.objects["scan_" + scan]
    # UVs
    bpy.ops.object.select_all(action="DESELECT"); t.select_set(True); bpy.context.view_layer.objects.active = t
    if not t.data.uv_layers: t.data.uv_layers.new(name="UVMap")
    bpy.ops.object.mode_set(mode="EDIT"); bpy.ops.mesh.select_all(action="SELECT")
    bpy.ops.uv.smart_project(angle_limit=math.radians(60), island_margin=0.01, area_weight=1.0)
    bpy.ops.object.mode_set(mode="OBJECT")
    # target image, pre-filled with the body colour, in a per-part material
    img = bpy.data.images.new(f"{prim}_baked", RES, RES); img.generated_color = BODY
    m = bpy.data.materials.new(f"body_{prim}"); m.use_nodes = True
    nt = m.node_tree; bsdf = nt.nodes["Principled BSDF"]
    bsdf.inputs["Roughness"].default_value = 0.55
    tex = nt.nodes.new("ShaderNodeTexImage"); tex.image = img
    nt.links.new(tex.outputs["Color"], bsdf.inputs["Base Color"])
    nt.nodes.active = tex
    t.data.materials.clear(); t.data.materials.append(m)
    # bake
    s.select_set(True); t.select_set(True); bpy.context.view_layer.objects.active = t
    bpy.ops.object.bake(type="DIFFUSE", pass_filter={"COLOR"})
    # missed rays are written as exact black (alpha stays 1): fill them with the body colour
    px = np.empty(RES * RES * 4, np.float32); img.pixels.foreach_get(px); px = px.reshape(-1, 4)
    miss = px[:, :3].sum(1) < 0.004; px[miss] = BODY
    img.pixels.foreach_set(px.ravel()); img.update()
    print(f"  {prim}: {miss.mean() * 100:.0f} % texels filled with the body colour")
    img.pack()
    print("baked", prim, "<-", s.name)

for o in appended:
    bpy.data.objects.remove(o, do_unlink=True)
bpy.ops.outliner.orphans_purge(do_recursive=True)
out = bpy.data.filepath
bpy.ops.wm.save_mainfile()
bpy.ops.export_scene.gltf(filepath=os.path.splitext(out)[0] + ".glb", export_format="GLB", export_extras=True,
                          export_yup=True, export_apply=True, export_image_format="JPEG")
print("written", out)
