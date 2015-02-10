%module timedomaineuler
%{
  #include "solutionatgp.h"
  #include "test.h"
  #include "tube.h"
%}

typedef double d;

namespace td{
  class SolutionAtGp {
    d rho_,m_=0,rhoE_=0;
  public:
    // Dependent variables
    const d& rho() const;
    const d& m() const;
    const d& rhoE() const;
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
    void setData(d rho,d m=0,d rhoE=0);
  };
  class SolutionInstance{
  public:
    SolutionInstance(int gp);
    ~SolutionInstance(){}
    d getTime() const;
    void setTime(d t);
    void set(us i,SolutionAtGp& sol);
    SolutionAtGp& get(us i);
    void setrho(d rho);
  };

  class Tube{
  public:
    Tube(double L,int gp);
    ~Tube(){}
    SolutionInstance& getSol() { return sol;}
    void setSol(const SolutionInstance& sol) {this->sol=sol;}
    void DoIntegration(d dt);
    d getTime(){return t;}
  };
}

