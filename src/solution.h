#pragma once
#ifndef _SOLUTION_H_
#define _SOLUTION_H_


#include "vtypes.h"
#include "geom.h"
#include "globalconf.h"

namespace td{
  SPOILNAMESPACE

  extern tasystem::Globalconf gc;

  class SolutionAtGp
  {
    d rho_,m_=0,rhoE_=0;
  public:
    // Dependent variables
    const d& rho() const {return rho_;}
    const d& m() const {return m_;} // which is rho*u
    const d& rhoE() const {return rhoE_;} // which is rho*E
    // Derived from dependent
    d u() const {return m()/rho();}
    d ekin() const {return 0.5*rho()*pow(u(),2);}
    d estat() const {return rhoE()-ekin();}
    d p() const {return estat()*(gc.gas.gamma(gc.T0)-1);}

    d Cflux() const {return m();}
    d Mflux() const {return pow(m(),2)/rho()+p();}
    d Eflux() const {return (rhoE()+gc.p0/(gc.gas.gamma(gc.T0)-1)+p()+gc.p0)*u();}
    SolutionAtGp();
    ~SolutionAtGp(){}
    void set(d rho,d m=0,d rhoE=0){
      rho_=rho;
      m_=m;
      rhoE_=rhoE;
    }

  };
  

  class SolutionInstance{
    vector<SolutionAtGp> gps;
    d time=0;
    int nr=0;
  public:
    SolutionInstance(d TimeInstance,int gp);
    ~SolutionInstance(){}
    d getTime() const {return time;}
    void setTime(d t) {time=t;}
    void set(us i,SolutionAtGp& sol){ gps.at(i)=sol;}
    SolutionAtGp& get(us i){ return gps.at(i); }

    void setrho(d rho);
    int safe(const char* dir);
  };

} // namespace td
#endif /* _SOLUTION_H_ */

