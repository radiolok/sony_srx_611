"""Assemble the primitive model (prim_cq.py STLs) into the same joint hierarchy as the scan model.

blender -b --python tools/model3d/build_prim_blend.py -- <prim_dir> <model_dir>

Writes <model_dir>/srx611_prim.{blend,glb}. Node names and pivots are identical to srx611.glb
(SRX611 > J1 > J2 > J3 > J4), so a viewer can load either model.
"""
import bpy, sys, json, os, math
from mathutils import Matrix
argv = sys.argv[sys.argv.index("--") + 1:]
prim, model = map(os.path.abspath, argv[:2])
J = json.load(open(os.path.join(model, "joints.json")))
P = json.load(open(os.path.join(prim, "parts.json")))
L1, L2 = J["L1"], J["L2"]

bpy.ops.wm.read_factory_settings(use_empty=True)
sc = bpy.context.scene; sc.unit_settings.system = "METRIC"

def empty(name, parent, loc, size=0.05):
    e = bpy.data.objects.new(name, None); e.empty_display_type = "ARROWS"; e.empty_display_size = size
    sc.collection.objects.link(e); e.parent = parent; e.location = loc; return e

def material(name, rgb, rough, metal=0.0):
    m = bpy.data.materials.new(name); m.use_nodes = True
    b = m.node_tree.nodes["Principled BSDF"]
    b.inputs["Base Color"].default_value = (*rgb, 1); b.inputs["Roughness"].default_value = rough
    b.inputs["Metallic"].default_value = metal
    return m

MAT = dict(body=material("body", (0.80, 0.78, 0.71), 0.55), cable=material("cable", (0.02, 0.02, 0.022), 0.5),
           alu=material("alu", (0.80, 0.81, 0.83), 0.35, 1.0), steel=material("steel", (0.70, 0.71, 0.72), 0.25, 1.0))
N = {"root": empty("SRX611", None, (0, 0, 0), 0.15)}
N["J1"] = empty("J1", N["root"], (0, 0, 0), 0.12)
N["J2"] = empty("J2", N["J1"], (L1, 0, 0), 0.10)
N["J3"] = empty("J3", N["J2"], (L2, 0, 0), 0.08)
N["J4"] = empty("J4", N["J3"], (0, 0, 0), 0.06)

for name, info in P.items():
    bpy.ops.wm.stl_import(filepath=os.path.join(prim, name + ".stl"))
    o = bpy.context.selected_objects[0]; o.name = o.data.name = name
    o.parent = N[info["joint"]]; o.matrix_parent_inverse = Matrix.Identity(4); o.location = (0, 0, 0)
    o.data.materials.append(MAT[info["material"]])
    bpy.context.view_layer.objects.active = o
    bpy.ops.object.shade_auto_smooth(angle=math.radians(35))

for o, kind, lim in ((N["J1"], "rot_z", [-110, 110]), (N["J2"], "rot_z", [-150, 150]), (N["J3"], "loc_z", None), (N["J4"], "rot_z", None)):
    o["joint"] = kind
    if lim: o["limit_deg"] = lim
r = N["root"]; r["L1_m"] = L1; r["L2_m"] = L2
r["scan_pose"] = {"J1_deg": 0.0, "J2_deg": J["phi_deg"], "J3_m": 0.0, "J4_deg": 0.0}
r["source"] = "primitive model tools/model3d/prim_cq.py (CadQuery), dimensions from the LiDAR scan"
N["J2"].rotation_euler.z = math.radians(J["phi_deg"])  # default = scanned pose, same as srx611.glb

bpy.ops.wm.save_as_mainfile(filepath=os.path.join(model, "srx611_prim.blend"))
bpy.ops.export_scene.gltf(filepath=os.path.join(model, "srx611_prim.glb"), export_format="GLB",
                          export_extras=True, export_yup=True, export_apply=True)
print("written", model)
