#!/usr/bin/python

from numpy import *
from matplotlib.pyplot import *
from matplotlib import animation
from run import *
import sys


inst=0

parr=load('pdata.npy')
uarr=load('udata.npy')
# save(pdat,'p.npy')
imax=parr.shape[0]


amplitude=1    
fig = figure(figsize=(12,8))
ax = axes(xlim=(0,x[-1]),ylim=(-amplitude,amplitude))
grid('on')
line, = plot([],[],lw=2)

def init():
    line.set_data([], [])
    return line,


# print(imax)
    
def animatep(i):
    # update_progress(int(round(100*i/imax)))
    line.set_data(x,parr[i])
    return line,

# animp = animation.FuncAnimation(fig, animatep, init_func=init,
#                                frames=imax, interval=20, blit=True,repeat=False)
def animateu(i):
    # update_progress(int(round(100*i/imax)))
    line.set_data(x,uarr[i])
    return line,
print("Creating animation...")
animu = animation.FuncAnimation(fig, animateu, init_func=init,
                               frames=imax, interval=20, blit=True,repeat=False)

# print("Saving animation...")
# anim.save('p.mp4', fps=20, extra_args=['-vcodec', 'libx264'])

print("Showing animation...")
show()





