#include "tube.h"

namespace td{


  Tube::Tube(const segment::Geom& g):
    geom(g),
    gc(tasystem::Globalconf::airSTP(0,100,1))
  {


  }

};
