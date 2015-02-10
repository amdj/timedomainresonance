#pragma once

namespace td{

  typedef double d;
  typedef unsigned us;

  class SolutionAtGp {
    d rho_,m_=0,rhoE_=0;
  public:
    // Dependent variables
    const d& rho() const {return rho_;}
    const d& m() const {return m_;} // which is rho*u
    const d& rhoE() const {return rhoE_;} // which is rho*E
    // Derived from dependent
    d u() const;
    d ekin() const;
    d estat() const;
    d p() const;

    d Cflux() const;
    d Mflux() const;
    d Eflux() const;
    SolutionAtGp();
    ~SolutionAtGp(){}
    void setData(d rho,d m=0,d rhoE=0){
      rho_=rho;
      m_=m;
      rhoE_=rhoE;
    }
  };
} // namespace td






