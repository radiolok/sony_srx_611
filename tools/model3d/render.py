"""Tiny textured z-buffer renderer. usage: render.py mesh.npz tex.jpg out.png yaw pitch [mask.npy] [center x,y,z] [dist]"""
import numpy as np, sys
from PIL import Image
def look(yaw,pitch):
    y,p=np.radians(yaw),np.radians(pitch)
    fwd=np.array([np.cos(p)*np.sin(y),np.sin(p),np.cos(p)*np.cos(y)])  # camera looks along -fwd
    up=np.array([0,1.,0]); r=np.cross(up,fwd); r/=np.linalg.norm(r); u=np.cross(fwd,r)
    return np.stack([r,u,fwd])
def render(pos,uv,p,tex,yaw,pitch,mask=None,center=None,dist=None,N=900,fov=40):
    tri=p[:,:,0]; tuv=p[:,:,1]
    if mask is not None: tri,tuv=tri[mask],tuv[mask]
    used=pos[np.unique(tri)]
    if center is None: center=(used.min(0)+used.max(0))/2
    rad=np.linalg.norm(used-center,axis=1).max()
    if dist is None: dist=rad/np.tan(np.radians(fov/2))*1.05
    R=look(yaw,pitch); cam=center+R[2]*dist
    v=(pos-cam)@R.T; z=-v[:,2]; f=N/2/np.tan(np.radians(fov/2))
    sx=v[:,0]/np.maximum(z,1e-6)*f+N/2; sy=N/2-v[:,1]/np.maximum(z,1e-6)*f
    zb=np.full((N,N),np.inf); img=np.full((N,N,3),255,np.uint8)
    H,W,_=tex.shape
    # shading by normal
    a,b,c=pos[tri[:,0]],pos[tri[:,1]],pos[tri[:,2]]
    n=np.cross(b-a,c-a); n/=np.linalg.norm(n,axis=1,keepdims=True)+1e-12
    shade=0.55+0.45*np.abs(n@R[2])
    for k in range(len(tri)):
        i=tri[k]; X=sx[i]; Y=sy[i]; Z=z[i]
        if (Z<=0.01).any(): continue
        x0,x1=int(max(X.min(),0)),int(min(X.max(),N-1)); y0,y1=int(max(Y.min(),0)),int(min(Y.max(),N-1))
        if x0>x1 or y0>y1: continue
        xs,ys=np.meshgrid(np.arange(x0,x1+1)+.5,np.arange(y0,y1+1)+.5)
        d=(Y[1]-Y[2])*(X[0]-X[2])+(X[2]-X[1])*(Y[0]-Y[2])
        if abs(d)<1e-9: continue
        l0=((Y[1]-Y[2])*(xs-X[2])+(X[2]-X[1])*(ys-Y[2]))/d
        l1=((Y[2]-Y[0])*(xs-X[2])+(X[0]-X[2])*(ys-Y[2]))/d
        l2=1-l0-l1; ins=(l0>=-1e-3)&(l1>=-1e-3)&(l2>=-1e-3)
        if not ins.any(): continue
        zz=l0*Z[0]+l1*Z[1]+l2*Z[2]
        sub=zb[y0:y1+1,x0:x1+1]; m=ins&(zz<sub)
        if not m.any(): continue
        sub[m]=zz[m]
        U=uv[tuv[k]]; uu=l0*U[0,0]+l1*U[1,0]+l2*U[2,0]; vv=l0*U[0,1]+l1*U[1,1]+l2*U[2,1]
        px=tex[np.clip(((1-vv[m])*H).astype(int),0,H-1),np.clip((uu[m]*W).astype(int),0,W-1)]
        img[y0:y1+1,x0:x1+1][m]=(px*shade[k]).astype(np.uint8)
    return img
if __name__=="__main__":
    d=np.load(sys.argv[1]); tex=np.asarray(Image.open(sys.argv[2]).convert('RGB'))
    mask=np.load(sys.argv[6]) if len(sys.argv)>6 and sys.argv[6]!='-' else None
    center=np.array([float(x) for x in sys.argv[7].split(',')]) if len(sys.argv)>7 else None
    dist=float(sys.argv[8]) if len(sys.argv)>8 else None
    img=render(d['pos'],d['uv'],d['p'].reshape(-1,3,2),tex,float(sys.argv[4]),float(sys.argv[5]),mask,center,dist)
    Image.fromarray(img).save(sys.argv[3])
