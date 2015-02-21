#include "solutioninstance.h"

namespace td{

  SolutionInstance::SolutionInstance(int gp,d rho)
  {
    TRACE(12,"SolutionInstance::SolutionInstance()");
    rho_=vd(gp,fillwith::zeros);
    m_=vd(gp,fillwith::zeros);
    rhoE_=vd(gp,fillwith::zeros);

  }
  void SolutionInstance::setrho(d rho)  {
    TRACE(15,"SolutionInstance::setrho()");
    rho_=ones(rho_.size())*rho;
  } // setrho()

}   // namespace td









