"""Preview renders of the segmentation. usage: labrender.py mesh.npz labels.npy texture.jpg out_prefix"""
import numpy as np, sys, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from render import render
from PIL import Image
Image.MAX_IMAGE_PIXELS = None
mesh, labels, texf, out = sys.argv[1:5]
d = np.load(mesh); lab = np.load(labels); P = d['p'].reshape(-1, 3, 2)
cols = np.array([[200,60,60],[60,160,60],[60,90,220],[0,190,190],[230,170,0],[150,60,180],[240,90,170]], np.uint8)  # base link1 link2 quill_top tool cable_arc cable_s
P2 = P.copy(); P2[:, :, 1] = np.arange(len(P) * 3).reshape(-1, 3)
uv = np.repeat(np.c_[(np.maximum(lab, 0) + .5) / len(cols), np.full(len(lab), .5)], 3, axis=0)
m = lab >= 0
ims = [render(d['pos'], uv, P2, cols[None], a, p, m, N=600) for a, p in ((0,15),(90,15),(180,15),(270,15),(0,89),(200,-30))]
W = Image.new('RGB', (1800, 1200), 'white')
for k, im in enumerate(ims): W.paste(Image.fromarray(im), ((k % 3) * 600, (k // 3) * 600))
W.save(out + '_labels.png')
tex = np.asarray(Image.open(texf).convert('RGB'))
ims = [render(d['pos'], d['uv'], P, tex, a, p, m, N=600) for a, p in ((0,15),(90,15),(270,15))]
W = Image.new('RGB', (1800, 600), 'white')
for k, im in enumerate(ims): W.paste(Image.fromarray(im), (k * 600, 0))
W.save(out + '_textured.png')
