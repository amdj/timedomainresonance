#!/usr/bin/python

from numpy import *
from matplotlib.pyplot import *

pfile=loadtxt('results/p.dat')
gp=300
pend=zeros(floor(pfile.shape[0]/gp))
for i in range(pend.size):
    pend[i]=pfile[(i+1)*gp-1,1]

plot(pend)
show()
