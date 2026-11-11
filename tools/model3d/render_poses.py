"""Render the articulated model in several poses (Cycles CPU, headless) to check the joint pivots.

blender -b emu/model/srx611.blend --python tools/model3d/render_poses.py -- <out.png>
"""
import bpy, sys, math
from mathutils import Vector
out = sys.argv[sys.argv.index("--") + 1]
sc = bpy.context.scene; O = bpy.data.objects
sc.render.engine = "CYCLES"; sc.cycles.device = "CPU"; sc.cycles.samples = 24
sc.render.resolution_x = sc.render.resolution_y = 480; sc.render.film_transparent = False
w = bpy.data.worlds.new("w"); w.use_nodes = True
w.node_tree.nodes["Background"].inputs[0].default_value = (1, 1, 1, 1); w.node_tree.nodes["Background"].inputs[1].default_value = 0.55
sc.view_settings.view_transform = "Standard"
sun = bpy.data.objects.new("sun", bpy.data.lights.new("sun", "SUN")); sc.collection.objects.link(sun)
sun.data.energy = 3.0; sun.rotation_euler = (math.radians(40), math.radians(15), math.radians(-30))
sc.world = w
cam = bpy.data.objects.new("cam", bpy.data.cameras.new("cam")); sc.collection.objects.link(cam); sc.camera = cam
cam.data.lens = 35
poses = [("scan pose", None), ("zero (straight)", (0, 0, 0, 0)), ("J1=+60 J2=-90", (60, -90, 0, 0)),
         ("J1=-45 J2=+120 Z=-0.10", (-45, 120, -0.10, 0)), ("J4=+90 Z=-0.05", (0, 0, -0.05, 90)), ("J1=+100 J2=+150", (100, 150, 0, 0))]
scan = dict(O["SRX611"]["scan_pose"])
paths = []
for k, (name, q) in enumerate(poses):
    if q is None: q = (scan["J1_deg"], scan["J2_deg"], scan["J3_m"], scan["J4_deg"])
    O["J1"].rotation_euler.z = math.radians(q[0]); O["J2"].rotation_euler.z = math.radians(q[1])
    O["J3"].location.z = q[2]; O["J4"].rotation_euler.z = math.radians(q[3])
    cam.location = Vector((1.25, -1.25, 1.05)); d = Vector((0.15, 0, 0.42)) - cam.location
    cam.rotation_euler = d.to_track_quat("-Z", "Y").to_euler()
    p = f"{out}.{k}.png"; sc.render.filepath = p; bpy.ops.render.render(write_still=True); paths.append((p, name))
import json; open(out + ".json", "w").write(json.dumps(paths))
