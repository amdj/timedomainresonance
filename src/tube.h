#pragma once 
#ifndef _TUBE_H_
#define _TUBE_H_

#include "geom.h"
#include "globalconf.h"
#include "solution.h"


namespace td{

  extern tasystem::Globalconf gc;

  class Tube{
    d dx,L;                     // Grid spacing, total length
    int gp;                     // Number of gridpoints
    SolutionInstance sol; // Solutions at time instances
    d t=0;                // Current time
    d pleft(d t);         // Compute pressure bc
    
  public:
    Tube(d L,int gp);
    SolutionInstance& getSol() { return sol;}
    void setSol(const SolutionInstance& sol) {this->sol=sol;}
    void DoIntegration(d dt);
    d getTime(){return t;}
  };

}                  // namespace td
#endif /* _TUBE_H_ */
