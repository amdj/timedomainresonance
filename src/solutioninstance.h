#pragma once
#include "solutionatgp.h"
#include "globalconf.h"

namespace td{
  SPOILNAMESPACE

  enum data{
    p,u
  };

  extern tasystem::Globalconf gc;

  class SolutionInstance{
    vector<SolutionAtGp> gps;
    d time=0;
  public:
    SolutionInstance(int gp);
    ~SolutionInstance(){}
    d getTime() const {return time;}
    void setTime(d t) {time=t;}
    void set(us i,SolutionAtGp& sol){ gps.at(i)=sol;}
    SolutionAtGp& get(us i){ return gps.at(i); }

    void setrho(d rho);
    int save(std::ofstream&,data d);
  };

} // namespace td

