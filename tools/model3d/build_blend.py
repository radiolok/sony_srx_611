"""Build the articulated SRX-611 model in Blender from the per-link OBJs and cables.json of segment.py.

blender -b --python tools/model3d/build_blend.py -- <seg_dir> <out_dir>

Hierarchy (Z up, metres, origin = J1 axis on the mounting surface, +X = forward = J1 mid-stroke):
  SRX611 > base
         > J1 (rot Z) > link1, cable_arc
                      > J2 (rot Z, at x=L1) > link2   (only the main cable is modelled)
                                            > J3 (slide Z, at x=L2) > J4 (rot Z) > quill_top, tool, spline_shaft
(owner: the top box turns with J4; the lower unit has its own 45-degree axis, driven through gears
 when the quill is raised — not modelled yet)
Zero pose = both arms straight along +X. The scanned pose is the default pose
(J2 = phi from joints.json) and is also stored in the custom property scan_pose.
"""
import bpy, sys, json, os, math
from mathutils import Matrix, Vector
argv = sys.argv[sys.argv.index("--") + 1:]
seg, out = map(os.path.abspath, argv[:2])
J = json.load(open(os.path.join(seg, "joints.json")))
C = json.load(open(os.path.join(seg, "cables.json")))
L1, L2, phi = J["L1"], J["L2"], math.radians(J["phi_deg"])
J2 = Vector((J["J2"][0], J["J2"][1], 0))
SHAFT_R = 0.025                      # spline shaft above the housing (doc §2)
SHAFT_Z = (0.40, J["housing_top"] + 0.02)

bpy.ops.wm.read_factory_settings(use_empty=True)
sc = bpy.context.scene
sc.unit_settings.system = "METRIC"

def empty(name, parent, loc, size=0.05):
    e = bpy.data.objects.new(name, None); e.empty_display_type = "ARROWS"; e.empty_display_size = size
    sc.collection.objects.link(e); e.parent = parent; e.location = loc; return e

def attach(o, parent, world_to_local):
    o.data.transform(world_to_local)  # scan-pose robot coords -> joint-local, zero-pose coords
    o.parent = parent; o.matrix_parent_inverse = Matrix.Identity(4)
    o.location = (0, 0, 0); o.rotation_euler = (0, 0, 0)
    for p in o.data.polygons: p.use_smooth = True
    return o

def load(name, parent, world_to_local):
    bpy.ops.wm.obj_import(filepath=os.path.join(seg, name + ".obj"), forward_axis="Y", up_axis="Z")
    o = bpy.context.selected_objects[0]; o.name = name; o.data.name = name
    return attach(o, parent, world_to_local)

def material(name, rgb, rough, metal=0.0):
    m = bpy.data.materials.new(name); m.use_nodes = True
    b = m.node_tree.nodes["Principled BSDF"]
    b.inputs["Base Color"].default_value = (*rgb, 1); b.inputs["Roughness"].default_value = rough
    b.inputs["Metallic"].default_value = metal
    return m

def tube(name, pts, radius, parent, world_to_local, mat):
    cu = bpy.data.curves.new(name, "CURVE"); cu.dimensions = "3D"
    cu.bevel_depth = radius; cu.bevel_resolution = 3; cu.use_fill_caps = True; cu.resolution_u = 6
    sp = cu.splines.new("NURBS"); sp.points.add(len(pts) - 1)
    for p, q in zip(sp.points, pts): p.co = (*q, 1)
    sp.use_endpoint_u = True; sp.order_u = 4
    o = bpy.data.objects.new(name, cu); sc.collection.objects.link(o)
    bpy.context.view_layer.objects.active = o; o.select_set(True)
    bpy.ops.object.convert(target="MESH"); o.select_set(False)
    o.data.materials.append(mat)
    return attach(o, parent, world_to_local)

root = empty("SRX611", None, (0, 0, 0), 0.15)
j1 = empty("J1", root, (0, 0, 0), 0.12)
j2 = empty("J2", j1, (L1, 0, 0), 0.10)
j3 = empty("J3", j2, (L2, 0, 0), 0.08)
j4 = empty("J4", j3, (0, 0, 0), 0.06)

# scan pose: link-2 frame = rotate phi about J2; world->local = inverse
I = Matrix.Identity(4)
to_j2 = Matrix.Rotation(-phi, 4, "Z") @ Matrix.Translation(-J2)
to_j3 = Matrix.Translation(-Vector((L2, 0, 0))) @ to_j2
load("base", root, I)
load("link1", j1, I)
load("link2", j2, to_j2)
load("quill_top", j4, to_j3)
load("tool", j4, to_j3)

# foot flange (photo IMG_3590: round flange, 4 bolts; scan: r 110 mm at the table, 78 mm column above h 60 mm)
m_body = material("body", (0.72, 0.70, 0.64), 0.6)
COL = Vector((*J["column_offset_m"], 0))
bpy.ops.mesh.primitive_cylinder_add(vertices=48, radius=0.110, depth=0.012, location=COL + Vector((0, 0, 0.006)))
fl = bpy.context.active_object; fl.name = fl.data.name = "foot_flange"
bpy.ops.mesh.primitive_cone_add(vertices=48, radius1=0.104, radius2=0.079, depth=0.050, location=COL + Vector((0, 0, 0.037)))
cn = bpy.context.active_object; cn.name = cn.data.name = "foot_cone"
for o in (fl, cn):
    o.data.materials.append(m_body); o.parent = root

m_cable = material("cable", (0.025, 0.025, 0.028), 0.55)
m_steel = material("steel", (0.75, 0.75, 0.76), 0.3, 1.0)
tube("cable_arc", C["cable_arc"]["smooth"], C["cable_arc"]["radius"], j1, I, m_cable)

# spline shaft inside the housing: only seen when J3 moves (the scan has the visible ends only)
bpy.ops.mesh.primitive_cylinder_add(vertices=24, radius=SHAFT_R, depth=SHAFT_Z[1] - SHAFT_Z[0],
                                    location=(0, 0, sum(SHAFT_Z) / 2))
sh = bpy.context.active_object; sh.name = sh.data.name = "spline_shaft"; sh.data.materials.append(m_steel)
sh.parent = j4

mat = bpy.data.materials.get("scan")
if mat:
    mat.name = "srx611_scan"
    for n in mat.node_tree.nodes:
        if n.type == "BSDF_PRINCIPLED":
            n.inputs["Roughness"].default_value = 0.8
            if "Specular IOR Level" in n.inputs: n.inputs["Specular IOR Level"].default_value = 0.2

# joint limits (Kapusi 2022: axis 1 220 deg total, axis 2 +-150 deg) — informational
for o, kind, lim in ((j1, "rot_z", [-110, 110]), (j2, "rot_z", [-150, 150]), (j3, "loc_z", None), (j4, "rot_z", None)):
    o["joint"] = kind
    if lim: o["limit_deg"] = lim
root["L1_m"] = L1; root["L2_m"] = L2; root["scan_scale"] = J["scale"]
root["scan_pose"] = {"J1_deg": 0.0, "J2_deg": J["phi_deg"], "J3_m": 0.0, "J4_deg": 0.0}
root["source"] = "3dScannerApp LiDAR scan Untitled_Scan_11_28_02 (2026-11-11), tools/model3d/segment.py"

j2.rotation_euler.z = phi  # default = scanned pose
bpy.ops.file.pack_all()
bpy.ops.wm.save_as_mainfile(filepath=os.path.join(out, "srx611.blend"))
bpy.ops.export_scene.gltf(filepath=os.path.join(out, "srx611.glb"), export_format="GLB",
                          export_extras=True, export_yup=True, export_apply=False)
print("written", out)
