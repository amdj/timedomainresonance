// solutioninstance.h
//
// Author: J.A. de Jong 
//
// Description:
//
//////////////////////////////////////////////////////////////////////
#pragma once
#ifndef SOLUTIONINSTANCE_H
#define SOLUTIONINSTANCE_H 1

#include "vtypes.h"
#include "globalconf.h"

namespace td{
  SPOILNAMESPACE
  extern tasystem::Globalconf gc;

  class SolutionInstance{

    vd rho_,m_,rhoE_;
    d time=0;
  public:
    SolutionInstance(int gp,d rho=1.2);
    ~SolutionInstance(){}
    d getTime() const {return time;}
    void setTime(d t) {time=t;}

    vd& rho_ref(){ return rho_;}
    vd& m_ref() {return m_;}
    vd& rhoE_ref() {return rhoE_;}    
    const vd& rho() const {return rho_;}
    const vd& m() const {return m_;}
    const vd& rhoE() const {return rhoE_;}
    vd p() const {return estat()*(gc.gas.gamma(gc.T0)-1);}
    vd u() const {return m()/rho();}
    vd ekin() const { return 0.5*rho()%pow(u(),2);}
    vd estat() const {return rhoE()-ekin();}
    vd Cflux() const {return m();}
    vd Mflux() const {return pow(m(),2)/rho()+p();}
    vd Eflux() const {return (rhoE()+gc.p0/(gc.gas.gamma(gc.T0)-1)+p()+gc.p0)%u();}

    void setrho(d rho);

  };

} // namespace td



#endif // SOLUTIONINSTANCE_H
//////////////////////////////////////////////////////////////////////

