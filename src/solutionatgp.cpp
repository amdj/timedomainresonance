#include "solutionatgp.h"
#include "globalconf.h"


TRACETHIS

namespace td{

  extern tasystem::Globalconf gc;

  SolutionAtGp::SolutionAtGp() {
    rho_=gc.rho0();
  }
  d SolutionAtGp::u() const {return m()/rho();}
  d SolutionAtGp::ekin() const {return 0.5*rho()*pow(u(),2);}
  d SolutionAtGp::estat() const {return rhoE()-ekin();}
  d SolutionAtGp::p() const {return estat()*(gc.gas.gamma(gc.T0)-1);}

  d SolutionAtGp::Cflux() const {return m();}
  d SolutionAtGp::Mflux() const {return pow(m(),2)/rho()+p();}
  d SolutionAtGp::Eflux() const {return (rhoE()+gc.p0/(gc.gas.gamma(gc.T0)-1)+p()+gc.p0)*u();}

}   // namespace td









