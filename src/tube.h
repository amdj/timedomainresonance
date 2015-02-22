// tube.h
//
// Author: J.A. de Jong 
//
// Description:
//
//////////////////////////////////////////////////////////////////////
#pragma once
#ifndef TUBE_H
#define TUBE_H 1

#include "solutioninstance.h"
#include "globalconf.h"

namespace td {

  typedef double d;

  class Tube {
  public:
    d dx, L;              // Grid spacing, total length
    int gp;               // Number of gridpoints
    SolutionInstance sol; // Solutions at time instances
    d pleft(d t);         // Compute pressure bc
    virtual SolutionInstance Integrate(d dt) = 0;

  public:
    Tube(double L, int gp) throw(int);
    virtual ~Tube() {}
    SolutionInstance &getSol() { return sol; }
    void setSol(const SolutionInstance &sol) { this->sol = sol; }
    void DoIntegration(d dt, int n = 1);
    d getTime() { return sol.getTime(); }
  };
  class TubeLF : public Tube { // Using Lax-Friedrichs method
  protected:
    virtual SolutionInstance Integrate(d dt);
  public:
    using Tube::Tube;

  };
  class TubeMCM : public Tube { // Using Lax-Friedrichs method
  protected:
    virtual SolutionInstance Integrate(d dt);
  public:
    using Tube::Tube;

  };
} // namespace td


#endif // TUBE_H
//////////////////////////////////////////////////////////////////////



