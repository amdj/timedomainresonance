#include "solutioninstance.h"

namespace td{

  SolutionInstance::SolutionInstance(int gp)
  {
    TRACE(12,"SolutionInstance::SolutionInstance()");
    gps.resize(gp);
  }
  void SolutionInstance::setrho(d rho)  {
    TRACE(15,"SolutionInstance::setrho()");

    for(auto gp=gps.begin();gp!=gps.end();gp++){
      gp->setData(rho);
    }
  } // setrho()
  vd SolutionInstance::getrho() const{
    return gpsol_to_python(gps,&SolutionAtGp::rho);
  }
  vd SolutionInstance::getp() const{
    return gpsol_to_python(gps,&SolutionAtGp::p);
  }
  int SolutionInstance::save(std::ofstream& str,data d){
    TRACE(15,"SolutionInstance::save()");
    if(d==data::p)
      for(us j=0;j<gps.size();j++){
        SolutionAtGp& solgp=get(j);
        str << j << "\t" <<solgp.p() << "\n";
      }
    else if(d==data::u)
      for(us j=0;j<gps.size();j++){
        SolutionAtGp& solgp=get(j);
        str << j << "\t" <<solgp.u() << "\n";
      }
    return 0;
  }

}   // namespace td









