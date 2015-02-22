#!/usr/bin/python

if(!os.path.isfile('timedomaineuler.py')):
    os.system('cmake . && make')
from timedomaineuler import *

from numpy import *
import os
import sys
from argparse import ArgumentParser
import argparse

parser=ArgumentParser(description="Compute response to tube\
with sinusoidal pressure boundary condition",\
 formatter_class=argparse.ArgumentDefaultsHelpFormatter)
parser.add_argument('scheme',help="Scheme to use, either LF (Lax-Friedrichs) or\
 (MCM) MacCormack",choices=["LF","MCM"])
parser.add_argument('-f','--freq',type=float,dest="f",default=85.785,\
                  help="Frequency of oscillation")
parser.add_argument('-L','--length',type=float,dest="L",default=1.0,\
                  help="Tube length")
parser.add_argument('-g','--gridpoints',type=int,dest="gp",default=300,\
                  help="Number of gridpoints")
parser.add_argument('-c','--CFL',type=float,dest="CFL",default=0.5,\
                  help="CFL Nummber")
parser.add_argument('-n','--saves_per_period',type=int,dest="nr_p_period",
                  default=50,help="Number of saves per period")
parser.add_argument('-p','--periods',type=float,dest="periods",
                  default=10,help="Periods to compute")
args=parser.parse_args()

globals().update(vars(args))    #Put options in global namespace
print("Frequency:",f)


T=1/f
gc=cvar.gc #Reference!
dx=L/(gp-1);                    # Grid spacing
gc.setfreq(f)                   # Set frequency in gc (for c++)
x=linspace(0,L,gp)              # Grid. Not really needed
if scheme=="LF":
    tube=TubeLF(L,gp)
else:    
    tube=TubeMCM(L,gp)
dt=min(CFL*dx/gc.c0(),T/nr_p_period)

intsteps=int(floor(1./(gc.getfreq()*dt)/nr_p_period))   #Number of
                                                        #steps per save

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
