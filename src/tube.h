#pragma once 
#ifndef _TUBE_H_
#define _TUBE_H_

#include "solutioninstance.h"
#include "globalconf.h"

namespace td{

  typedef double d;

  class Tube{
    d dx,L;                     // Grid spacing, total length
    int gp;                     // Number of gridpoints
    SolutionInstance sol; // Solutions at time instances
    d t=0;                // Current time
    d pleft(d t);         // Compute pressure bc
    void Integrate(d dt);
  public:
    Tube(double L,int gp);
    ~Tube(){}
    SolutionInstance& getSol() { return sol;}
    void setSol(const SolutionInstance& sol) {this->sol=sol;}
    void DoIntegration(d dt,int n=1);
    d getTime(){return t;}
  };

}                  // namespace td
#endif /* _TUBE_H_ */
