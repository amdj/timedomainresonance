#!/usr/bin/python

from numpy import *
from matplotlib.pyplot import *
from matplotlib import animation
import sys


inst=0
print("Loading data...")
pdat=loadtxt('results/p.dat')
# save(pdat,'p.npy')

gp=300                          # Need to be taken from file

xmax=pdat[-1,0]
x=linspace(0,1,300)
        
fig = figure(figsize=(12,8))
ax = axes(xlim=(0,1),ylim=(-180,180))
grid('on')
line, = plot([],[],lw=2)

ponly=pdat[:,1]
imax=int(floor(pdat.shape[0]/gp))

p=array_split(ponly,imax)

def init():
    line.set_data([], [])
    return line,


# print(imax)
def update_progress(progress):
        sys.stdout.write('\r[{0}{1}] {2}%'.format('#'*int(floor(progress)),' '*int(ceil((100-progress))),progress))
    
def animate(i):
    update_progress(int(round(100*i/imax)))
    line.set_data(x,p[i])
    return line,
print("Creating animation...")
anim = animation.FuncAnimation(fig, animate, init_func=init,
                               frames=imax, interval=20, blit=True)
# print("Saving animation...")
# anim.save('p.mp4', fps=20, extra_args=['-vcodec', 'libx264'])

print("Showing animation...")
show()

