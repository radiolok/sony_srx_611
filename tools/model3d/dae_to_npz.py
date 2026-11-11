"""Read a 3dScannerApp Collada (.dae) mesh into an .npz (pos, uv, p). usage: dae_to_npz.py in.dae out.npz"""
import re, numpy as np, sys
def load(path):
    t=open(path).read()
    fa=re.findall(r'<float_array id="([^"]+)" count="\d+">([^<]*)</float_array>',t)
    pos=np.array(fa[0][1].split(),float).reshape(-1,3)
    uv=np.array(fa[1][1].split(),float).reshape(-1,2)
    inputs=re.findall(r'<input semantic="(\w+)" source="#([^"]+)" offset="(\d+)"',t)
    p=np.array(re.search(r'<p>([^<]*)</p>',t).group(1).split(),int)
    return pos,uv,inputs,p
if __name__=="__main__":
    pos,uv,inputs,p=load(sys.argv[1])
    print(pos.shape,uv.shape,inputs,p.shape)
    print("min",pos.min(0),"max",pos.max(0))
    np.savez(sys.argv[2],pos=pos,uv=uv,p=p)
