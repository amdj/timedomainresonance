#!/usr/bin/python

from timedomaineuler import *
from numpy import *
import sys
#Globalconf accessable with cvar.gc
f=85.785                                  #Frequency of oscillation


L=1.                                      #Length of tube
gp=300                                    #Number of gridpoints

nr_p_period=50                  #Number of save per oscillation period
CFL=0.5;                        # CFL number
periods=100                      #Number of periods to compute

T=1/f
gc=cvar.gc #Reference!
dx=L/(gp-1);                    # One left and right gp, so

gc.setfreq(f)
tube=TubeLF(L,gp)
dt=min(CFL*dx/gc.c0(),T/nr_p_period)

intsteps=int(floor(1./(gc.getfreq()*dt)/nr_p_period))
x=linspace(0,L,gp)

# Create tube instance
tube=TubeLF(L,gp)

# To create a nice progress bar

def update_progress(progress):
        nbars=60
        text1="\r[{0}{1}] {2}%".format('#'*int(floor(nbars*progress)),' '*int(nbars-floor(nbars*progress)),"%0.0f" %(100*progress))
        # text=",' '*(80-int(80*floor(progress))),progress)
        sys.stdout.write(text1)
        sys.stdout.flush()
if(__name__=="__main__"):

    # Create data storage
    uarr=zeros((nr_p_period*periods+1,gp),dtype=float)
    parr=zeros((nr_p_period*periods+1,gp),dtype=float)
    t=0.0
    i=0
    # Now we create the results
    imax=nr_p_period*periods
    print("Start time integration...")
    while(i<imax):
        update_progress(i/imax)
        sol=tube.getSol()
        uarr[i]=sol.u()
        parr[i]=sol.p()
        # Update solution
        t=sol.getTime()
        i+=1
        tube.DoIntegration(dt,intsteps)
    print("")
    print("Time integration done. Now saving data...")
    save('udata.npy',uarr)
    save('pdata.npy',parr)
    print("Saving data done. Exiting.")        
