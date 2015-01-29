#include "solution.h"
#include "geom.h"
#include "tube.h"



namespace td{
  SolutionAtGp::SolutionAtGp() {
    rho_=gc.rho0();
  }
  SolutionInstance::SolutionInstance(d time,int gp):
    time(time)
  {
    TRACE(15,"SolutionInstance::SolutionInstance()");
    gps.resize(gp);
  }
  void SolutionInstance::setrho(d rho)  {
    TRACE(15,"SolutionInstance::setrho()");

    for(auto gp=gps.begin();gp!=gps.end();gp++){
      gp->set(rho);
    }
  } // setrho()
  int SolutionInstance::safe(const char* dir){
    TRACE(15,"SolutionInstance::safe()");
    std::stringstream pfilename,ufilename,rhofilename;
    pfilename.str(""); ufilename.str(""); rhofilename.str("");
    pfilename << dir;
    ufilename << dir;
    rhofilename << dir;

    pfilename << "/p" << nr << ".dat";
    ufilename << "/u" << nr << ".dat";
    rhofilename << "/rho" << nr << ".dat";
    cout << pfilename.str() << "\n";

    std::ofstream p(pfilename.str());
    std::ofstream u(ufilename.str());
    std::ofstream rho(rhofilename.str());

    // Writing results for pressure to file
    p   << "#Pressure data vs gridpoint: t=" << time << "\n";
    u   << "#Velocity data vs gridpoint: t=" << time << "\n";
    rho << "#Density data vs gridpoint: t=" << time << "\n";
    for(us j=0;j<gps.size();j++){
      SolutionAtGp& solgp=get(j);
      p << j << "\t" <<solgp.p() << "\n";
      u << j << "\t" <<solgp.u() << "\n";
      rho << j << "\t" <<solgp.rho() << "\n";        
    }
    return 0;
  }
}   // namespace td

