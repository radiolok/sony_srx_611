"""Simplified SRX-611 arm from primitives (CadQuery), dimensions taken off the LiDAR scan (doc/robot_3d_model.md §8).

~/opt/venv-cadquery/bin/python tools/model3d/prim_cq.py <model_dir> <out_dir>

<model_dir> holds joints.json / cables.json from segment.py (emu/model). Writes:
  <out_dir>/<part>.stl            each part in the local frame of the joint that carries it
  <out_dir>/parts.json            part -> joint, material
  <model_dir>/srx611_prim.step    assembly in the zero pose (arms straight along +X)

Frames: metres, Z up, all joint frames at z = 0, so heights below are heights above the
mounting surface. J1 at the origin; J2 at (L1, 0); J3/J4 at (L1 + L2, 0) in the zero pose.
The gripper below the quill sleeve is not modelled yet (owner, 2026-11-11).
"""
import cadquery as cq, json, math, os, sys

model_dir, out = sys.argv[1:3]
os.makedirs(out, exist_ok=True)
J = json.load(open(os.path.join(model_dir, "joints.json")))
C = json.load(open(os.path.join(model_dir, "cables.json")))
L1, L2, PHI = J["L1"], J["L2"], math.radians(J["phi_deg"])

# ---- dimensions (m), from the scan slices img/3d/19-20 and photos doc/photos ----
FLANGE_R, FLANGE_H = 0.110, 0.012          # round foot flange, 4 bolts (IMG_3590)
CONE_R0, CONE_R1, CONE_TOP = 0.104, 0.079, 0.062
COLUMN_R, COLUMN_TOP = 0.077, 0.385
REAR_BOX = dict(x=(-0.145, -0.030), y=(-0.050, 0.100), z=(0.060, 0.370))   # connector box (IMG_3591)
ARM1_R1, ARM1_R2, ARM1_Z = 0.088, 0.066, (0.385, 0.475)
ARM2_R1, ARM2_R2, ARM2_Z = 0.066, 0.062, (0.465, 0.795)
GLAND = dict(x=0.33, r=0.030, h=0.030)      # main cable gland on the housing top, rear (IMG_3588)
SLEEVE_R, SLEEVE_Z = 0.036, (0.345, 0.465)  # aluminium quill sleeve below the housing
SHAFT_R, SHAFT_Z = 0.025, (0.400, 0.880)    # spline shaft (visible above the housing)
TOPBOX = dict(x=0.120, y=0.090, z=(0.875, 0.965))      # aluminium box on the shaft (IMG_3586)
TOPCON = dict(x=0.070, y=0.060, z=(0.965, 1.045))      # connectors / cable clamps on the box

def tapered_stadium(r1, r2, d, z0, z1, fillet=0.0):
    """Convex hull of circle(0,0,r1) and circle(d,0,r2), extruded from z0 to z1."""
    s = (r1 - r2) / d; c = math.sqrt(1 - s * s)
    p1u, p2u = (r1 * s, r1 * c), (d + r2 * s, r2 * c)
    p1l, p2l = (p1u[0], -p1u[1]), (p2u[0], -p2u[1])
    w = (cq.Workplane("XY", origin=(0, 0, z0)).moveTo(*p1u).lineTo(*p2u)
         .threePointArc((d + r2, 0), p2l).lineTo(*p1l).threePointArc((-r1, 0), p1u).close()
         .extrude(z1 - z0))
    if fillet:
        try: w = w.faces(">Z").edges().fillet(fillet)
        except Exception: pass
    return w

def cyl(r, z0, z1, x=0.0, y=0.0):
    return cq.Workplane("XY", origin=(x, y, z0)).circle(r).extrude(z1 - z0)

def box(xr, yr, zr):
    return cq.Workplane("XY").box(xr[1] - xr[0], yr[1] - yr[0], zr[1] - zr[0]).translate(
        ((xr[0] + xr[1]) / 2, (yr[0] + yr[1]) / 2, (zr[0] + zr[1]) / 2))

def tube(points, r, every=3):
    """Sweep a circle along a spline through every `every`-th centreline point (ends kept) — smooths scan noise."""
    sel = points[::every] if (len(points) - 1) % every == 0 else points[::every] + [points[-1]]
    pts = [cq.Vector(*p) for p in (sel if len(sel) >= 3 else points)]
    path = cq.Wire.assembleEdges([cq.Edge.makeSpline(pts)])
    t = (pts[1] - pts[0]).normalized()
    return cq.Workplane(cq.Plane(origin=pts[0], xDir=t.cross(cq.Vector(0, 0, 1)).normalized()
                                 if abs(t.z) < 0.99 else cq.Vector(1, 0, 0), normal=t)).circle(r).sweep(
        cq.Workplane().add(path), transition="round")

def to_j2(p):  # scan-pose robot frame -> J2 local zero-pose frame
    x, y = p[0] - J["J2"][0], p[1] - J["J2"][1]
    c, s = math.cos(-PHI), math.sin(-PHI)
    return (c * x - s * y, s * x + c * y, p[2])

parts = {}  # name -> (shape, joint, material)
# base (root frame; column coaxial with J1)
base = (cyl(FLANGE_R, 0, FLANGE_H)
        .union(cq.Workplane().add(cq.Solid.makeCone(CONE_R0, CONE_R1, CONE_TOP - FLANGE_H,
                                                    pnt=cq.Vector(0, 0, FLANGE_H))))
        .union(cyl(COLUMN_R, 0, COLUMN_TOP))
        .union(box(REAR_BOX["x"], REAR_BOX["y"], REAR_BOX["z"]).edges("|Z").fillet(0.012)))
parts["base"] = (base, "root", "body")
# link 1
parts["link1"] = (tapered_stadium(ARM1_R1, ARM1_R2, L1, *ARM1_Z, fillet=0.008), "J1", "body")
parts["cable_arc"] = (tube(C["cable_arc"]["smooth"], C["cable_arc"]["radius"], every=1), "J1", "cable")  # main cable only
# link 2 (J2 frame)
parts["link2"] = (tapered_stadium(ARM2_R1, ARM2_R2, L2, *ARM2_Z, fillet=0.015), "J2", "body")
gx = to_j2((GLAND["x"], 0, 0))[0]
parts["gland"] = (cyl(GLAND["r"], ARM2_Z[1], ARM2_Z[1] + GLAND["h"], gx, 0), "J2", "cable")
# quill (J4 frame: origin on the quill axis)
parts["sleeve"] = (cyl(SLEEVE_R, *SLEEVE_Z), "J4", "alu")
parts["spline_shaft"] = (cyl(SHAFT_R, *SHAFT_Z), "J4", "steel")
parts["top_box"] = (box((-TOPBOX["x"] / 2, TOPBOX["x"] / 2), (-TOPBOX["y"] / 2, TOPBOX["y"] / 2), TOPBOX["z"])
                    .edges("|Z").fillet(0.006), "J4", "alu")
parts["top_connectors"] = (box((-TOPCON["x"] / 2, TOPCON["x"] / 2), (-TOPCON["y"] / 2, TOPCON["y"] / 2), TOPCON["z"]),
                           "J4", "steel")

# STL per part (local frames) + parts.json
for n, (w, j, m) in parts.items():
    tol = 0.002 if n.startswith("cable") else 0.0004
    cq.exporters.export(w, os.path.join(out, n + ".stl"), tolerance=tol, angularTolerance=0.25 if n.startswith("cable") else 0.15)
json.dump({n: dict(joint=j, material=m) for n, (w, j, m) in parts.items()}, open(os.path.join(out, "parts.json"), "w"), indent=1)

# STEP assembly in the zero pose, nested like the joints
COL = dict(body=cq.Color(0.80, 0.78, 0.72), cable=cq.Color(0.05, 0.05, 0.05), alu=cq.Color(0.75, 0.76, 0.78),
           steel=cq.Color(0.60, 0.61, 0.63))
nodes = {"root": cq.Assembly(name="SRX611"), "J1": cq.Assembly(name="J1"), "J2": cq.Assembly(name="J2"),
         "J3": cq.Assembly(name="J3"), "J4": cq.Assembly(name="J4")}
for n, (w, j, m) in parts.items():
    nodes[j].add(w, name=n, color=COL[m])
nodes["J3"].add(nodes["J4"])
nodes["J2"].add(nodes["J3"], loc=cq.Location(cq.Vector(L2, 0, 0)))
nodes["J1"].add(nodes["J2"], loc=cq.Location(cq.Vector(L1, 0, 0)))
nodes["root"].add(nodes["J1"])
nodes["root"].export(os.path.join(model_dir, "srx611_prim.step"))
print("parts:", ", ".join(parts), "->", out)
