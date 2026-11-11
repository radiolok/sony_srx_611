"""Segment the 3dScannerApp mesh of the SRX-611 into rigid links, clean it, fit the cable centrelines.

usage: segment.py mesh.npz out_dir texture.jpg

Writes <out_dir>/{base,link1,link2,quill_top,tool}.obj (robot frame, Z up, metres, scan pose),
srx611.mtl + srx611_tex.jpg (texture cropped to the used rows), cables.json (centrelines of the
two cables, rebuilt as tubes by build_blend.py), joints.json and labels.npy (per scan triangle).

Robot frame: origin = J1 axis on the mounting surface, +X = arm direction in the scan pose
(owner: the arm looked straight ahead at scan time, J1 = mid-stroke = 0).
The scan is scaled so that J1-J2 / J2-quill equal the arm plate (C61-1173): see doc/robot_3d_model.md §2.
"""
import numpy as np, sys, json, os
from PIL import Image
Image.MAX_IMAGE_PIXELS = None

L1_PLATE, L2_PLATE = 0.349847, 0.249699
TABLE_Y = -0.845                       # mounting surface (largest horizontal plane), scan y
COLUMN = np.array([0.683, -1.128])     # column circle fit (scan x, z), y -0.80..-0.76
J2S = np.array([0.814, -0.792])        # J2 hub / arm-2 rear rounding
QS = np.array([0.878, -0.552])         # quill circle fit
NAMES = ['base', 'link1', 'link2', 'quill_top', 'tool', 'cable_arc', 'cable_s']

def main(mesh, out, texf):
    os.makedirs(out, exist_ok=True)
    d = np.load(mesh); pos = d['pos']; uv = d['uv'].copy(); P = d['p'].reshape(-1, 3, 2)
    # --- frame: scale from L2, J1 on the J2->column line at L1 (column fit is ~12 mm off, see doc)
    s = L2_PLATE / np.linalg.norm(QS - J2S)
    u = (COLUMN - J2S) / np.linalg.norm(COLUMN - J2S)
    J1S = J2S + u * L1_PLATE / s
    ex = (J2S - J1S) / np.linalg.norm(J2S - J1S); ey = np.array([ex[1], -ex[0]])  # Y = up x X
    def to_robot(p):
        h = p[..., [0, 2]] - J1S
        return np.stack([h @ ex, h @ ey, p[..., 1] - TABLE_Y], -1) * s
    R = to_robot(pos)
    q2 = lambda a: to_robot(np.array([a[0], 0, a[1]]))[:2]
    J2, Q, COL = q2(J2S), q2(QS), q2(COLUMN)
    phi = float(np.degrees(np.arctan2(*(Q - J2)[::-1])))

    # --- per-triangle features
    tri = P[:, :, 0]; c = R[tri].mean(1); xy = c[:, :2]; h = c[:, 2]
    a, b, cc = R[tri[:, 0]], R[tri[:, 1]], R[tri[:, 2]]
    n = np.cross(b - a, cc - a); n /= np.linalg.norm(n, axis=1, keepdims=True) + 1e-12
    def dseg(p, a, b):
        ab = b - a; t = ((p - a) @ ab) / (ab @ ab)
        return np.linalg.norm(p - (a + np.clip(t, 0, 1)[:, None] * ab), axis=1), t
    r1 = np.linalg.norm(xy, axis=1); rc = np.linalg.norm(xy - COL, axis=1); rq = np.linalg.norm(xy - Q, axis=1)
    d1, _ = dseg(xy, np.zeros(2), J2); d2, t2 = dseg(xy, J2, Q); dall, tall = dseg(xy, np.zeros(2), Q)
    HOUSING_TOP = 0.795 * s            # top of the arm-2 housing (scan y -0.05)
    near = (dall < 0.16) & (tall > -0.35) & (tall < 1.2) & (h > 0.006) & (h < 1.12)

    tool = near & (((rq < 0.045) & (h < 0.43)) | ((h < 0.375) & (rq < 0.12)))
    qtop = near & ~tool & (h > HOUSING_TOP) & (rq < 0.075)          # spline-shaft top + top unit
    link2 = near & ~tool & ~qtop & (d2 < 0.085) & (h >= 0.43) & (h <= HOUSING_TOP + 0.01) & ((h >= 0.475) | (t2 * L2_PLATE > 0.035))
    link1 = near & ~tool & ~qtop & ~link2 & (d1 < 0.11) & (h >= 0.37) & (h < 0.48)
    base = near & ~tool & ~qtop & ~link2 & ~link1 & (rc < 0.13) & (h < 0.385)
    rest = near & ~tool & ~qtop & ~link2 & ~link1 & ~base
    cable_s = rest & (h > HOUSING_TOP - 0.02) & (d2 < 0.10) & (t2 > 0.25)   # housing top -> top unit
    wrap = cable_s & (rq < 0.10) & (xy[:, 0] > Q[0] + 0.02)                # cable wrapped round the top unit
    qtop |= wrap; cable_s &= ~wrap
    cable_arc = rest & ~cable_s & ~wrap & (h > 0.30)
    base |= rest & ~cable_s & ~cable_arc & (rc < 0.25) & (h < 0.30)        # cable entry at the column back

    # --- cleaning
    shadow = (h < 0.03) & (rc > 0.105)                                      # table/shadow skirt around the foot
    flat = (h < 0.012) & (np.abs(n[:, 2]) > 0.8)                            # table surface inside the foot
    foot = h < 0.045                                                       # ragged foot edge -> primitive flange (build_blend.py)
    base &= ~shadow & ~flat & ~foot
    lab = np.full(len(c), -1)
    for k, m in enumerate([base, link1, link2, qtop, tool, cable_arc, cable_s]):
        lab[m & (lab < 0)] = k
    lab = drop_islands(lab, tri, len(pos))
    np.save(os.path.join(out, 'labels.npy'), lab)

    # --- texture: crop to the used rows
    tex = Image.open(texf); TW, TH = tex.size
    vmin = max(0.0, np.floor(uv[:, 1].min() * TH / 64) * 64 / TH)
    tex.crop((0, 0, TW, int(round((1 - vmin) * TH)))).save(os.path.join(out, 'srx611_tex.jpg'), quality=92)
    uv[:, 1] = (uv[:, 1] - vmin) / (1 - vmin)
    with open(os.path.join(out, 'srx611.mtl'), 'w') as f:
        f.write('newmtl scan\nKd 1 1 1\nmap_Kd srx611_tex.jpg\n')

    for k, nm in enumerate(NAMES[:5]):
        write_obj(os.path.join(out, nm + '.obj'), nm, P[lab == k], R, uv)
        print(nm, int((lab == k).sum()), 'tris')
    info = dict(L1=L1_PLATE, L2=L2_PLATE, scale=float(s), phi_deg=phi, J2=J2.tolist(), Q=Q.tolist(),
                housing_top=float(HOUSING_TOP), column_offset_m=COL.tolist(), table_y=TABLE_Y,
                J1_scan=J1S.tolist(), J2_scan=J2S.tolist(), Q_scan=QS.tolist(), X_axis_scan=ex.tolist())
    json.dump(info, open(os.path.join(out, 'joints.json'), 'w'), indent=1)
    print(json.dumps(info))
    cv = R[np.unique(tri[(lab == 5) | (lab == 6)])]
    cables = {
        # base side (lowest point at the column back) -> arc apex -> arm-2 housing top, rear
        'cable_arc': centreline(cv, (-0.14, 0.03, 0.38), (0.33, 0.0, 0.80)),
        # branch from the arc's down-leg -> bottom of the top unit on the quill
        'cable_s': centreline(cv, (0.42, 0.0, 0.95), (0.53, 0.0, 0.86)),
    }
    json.dump(cables, open(os.path.join(out, 'cables.json'), 'w'), indent=1)

def drop_islands(lab, tri, nv, keep=0.04):
    """Within each label, keep connected components with >= keep * largest component triangles."""
    for k in range(lab.max() + 1):
        idx = np.where(lab == k)[0]
        if not len(idx): continue
        parent = np.arange(nv)
        def find(x):
            while parent[x] != x: parent[x] = parent[parent[x]]; x = parent[x]
            return x
        for t in tri[idx]:
            r0 = find(t[0])
            for v in t[1:]:
                rv = find(v)
                if rv != r0: parent[rv] = r0
        roots = np.array([find(t[0]) for t in tri[idx]])
        ids, cnt = np.unique(roots, return_counts=True)
        small = set(ids[cnt < keep * cnt.max()])
        lab[idx[[r in small for r in roots]]] = -1
    return lab

def centreline(v, start, end, step=0.03, tube=0.05):
    """Cable centreline between two approximate end points: shortest path on a kNN graph of the
    cable surface points, resampled every `step`; each sample = mean of the points within `tube`
    that are nearest to it (the scan is one-sided, so this sits slightly towards the seen side)."""
    from scipy.sparse.csgraph import dijkstra
    from scipy.sparse import coo_matrix
    from scipy.spatial import cKDTree
    tree = cKDTree(v); pr = tree.query_pairs(0.04, output_type='ndarray')
    w = np.linalg.norm(v[pr[:, 0]] - v[pr[:, 1]], axis=1) ** 2   # squared: prefer short hops, follow the surface
    G = coo_matrix((w, (pr[:, 0], pr[:, 1])), shape=(len(v),) * 2).tocsr(); G = G.maximum(G.T)
    i0 = tree.query(start)[1]; i1 = tree.query(end)[1]
    _, pred = dijkstra(G, indices=i0, return_predecessors=True)
    path = [i1]
    while path[-1] != i0 and pred[path[-1]] >= 0: path.append(pred[path[-1]])
    path = v[path[::-1]]
    seg = np.r_[0, np.cumsum(np.linalg.norm(np.diff(path, axis=0), axis=1))]
    assert seg[-1] > 0, 'cable end points are not connected'
    ts = np.linspace(0, seg[-1], max(4, int(seg[-1] / step) + 1))
    samp = np.array([np.interp(ts, seg, path[:, k]) for k in range(3)]).T
    owner = cKDTree(samp).query(v)[1]; dd = np.linalg.norm(v - samp[owner], axis=1)
    pts, rad = [], []
    for i in range(len(samp)):
        m = (owner == i) & (dd < tube)
        if m.sum() >= 4:
            cen = v[m].mean(0); pts.append(cen); rad.append(np.median(np.linalg.norm(v[m] - cen, axis=1)))
        else:
            pts.append(samp[i])
    pts = np.array(pts)
    for _ in range(4):  # smoothing, ends fixed
        pts[1:-1] = 0.25 * pts[:-2] + 0.5 * pts[1:-1] + 0.25 * pts[2:]
    # smooth version for the tubes: smoothing B-spline (~6 mm tolerance), resampled at 25 points
    from scipy.interpolate import splprep, splev
    tck, _ = splprep(pts.T, s=len(pts) * 0.006 ** 2, k=3)
    smooth = np.array(splev(np.linspace(0, 1, 25), tck)).T
    return dict(points=pts.tolist(), smooth=smooth.tolist(), radius=float(np.clip(np.median(rad), 0.010, 0.020)), length=float(seg[-1]))

def write_obj(path, name, t, R, uv):
    vi = np.unique(t[:, :, 0]); ti = np.unique(t[:, :, 1])
    vm = -np.ones(len(R), int); vm[vi] = np.arange(len(vi)); tm = -np.ones(len(uv), int); tm[ti] = np.arange(len(ti))
    with open(path, 'w') as f:
        f.write(f'mtllib srx611.mtl\no {name}\n')
        f.writelines('v %.5f %.5f %.5f\n' % tuple(x) for x in R[vi])
        f.writelines('vt %.5f %.5f\n' % tuple(x) for x in uv[ti])
        f.write('usemtl scan\n')
        f.writelines('f %d/%d %d/%d %d/%d\n' % (vm[a] + 1, tm[b] + 1, vm[a2] + 1, tm[b2] + 1, vm[a3] + 1, tm[b3] + 1)
                     for (a, b), (a2, b2), (a3, b3) in t)

if __name__ == '__main__':
    main(*sys.argv[1:4])
