#include "geom.h"
#include "grid.h"
#include "tube.h"

using segment::Geom;
using segment::Grid;
int main(int argc,char *argv[]){
  SPOILNAMESPACE
  us gp=100;
  d L=1;
  Grid grid(gp,L);
  d radius=1.0;
  Geom g=Geom::CylinderBlApprox(grid,radius);

  td::Tube t(g);
  return 0;
}
