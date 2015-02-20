#pragma once
#include "solutionatgp.h"
#include "vtypes.h"

void do_arma_to_python(const vd& armavec,double** data,int* n);

namespace td{
  SPOILNAMESPACE

  template<typename funptr>
  vd gpsol_to_python(const vector<SolutionAtGp>& gps,funptr fun){
    int size=gps.size();
    vd result(size);
    for(int i=0;i<size;i++)
      result(i)=((gps[i]).*fun)();
    return result;
  }


  enum data{
    p,u
  };

  class SolutionInstance{
    vector<SolutionAtGp> gps;
    d time=0;
  public:
    SolutionInstance(int gp);
    ~SolutionInstance(){}
    d getTime() const {return time;}
    void setTime(d t) {time=t;}
    void setData(us i,SolutionAtGp& sol){ gps.at(i)=sol;}
    SolutionAtGp& get(us i){ return gps.at(i); }

    vd getp() const;
    vd getrho() const;
    void setrho(d rho);
    int save(std::ofstream&,data d);
  };

} // namespace td

