#pragma once 
#ifndef _TUBE_H_
#define _TUBE_H_

#include "geom.h"
#include "globalconf.h"
#include "solution.h"

namespace td{


  class Tube{

    segment::Geom geom;
    tasystem::Globalconf gc;
    vector<Solution> sols;
  public:
    Tube(const segment::Geom& g);
    Solution& getSol(int i=-1);

};



}                  // namespace td
#endif /* _TUBE_H_ */
