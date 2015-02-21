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
  protected:
    d dx, L;              // Grid spacing, total length
    int gp;               // Number of gridpoints
    SolutionInstance sol; // Solutions at time instances
    d t = 0;              // Current time
    d pleft(d t);         // Compute pressure bc
    virtual void Integrate(d dt) = 0;

  public:
    Tube(double L, int gp) throw(int);
    virtual ~Tube() {}
    SolutionInstance &getSol() { return sol; }
    void setSol(const SolutionInstance &sol) { this->sol = sol; }
    void DoIntegration(d dt, int n = 1);
    d getTime() { return t; }
  };
  class TubeLF : public Tube { // Using Lax-Friedrichs method
  protected:
    virtual void Integrate(d dt);

  public:
    using Tube::Tube;

  };
} // namespace td



#endif // TUBE_H
//////////////////////////////////////////////////////////////////////



