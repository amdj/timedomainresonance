#include "tube.h"
#include "tracer.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <boost/program_options.hpp>
TRACETHIS;

using geom::Geom;
using geom::Grid;
namespace po = boost::program_options;
using namespace td;
SPOILNAMESPACE;

// Directory for storage
const char* dir="results";



inline double min(d x,d y){return x<y?x:y;}

int main(int argc,char *argv[]){

  d f=100;


  po::options_description desc("Allowed options");
  desc.add_options()
    ("help", "Produce help message")
    ("frequency",po::value<d>(&f)->default_value(100))
    ;
  d T=1/f;
  d L=0.01;
  us gp=10;

  d dx=L/gp;
  d CFL=0.5;
  // This is questionable
  d dt=min(CFL*dx/gc.c0(),T/50);
  cout << "dt:" << dt <<"\n";
  cout << "dx:" << dx <<"\n";

  td::gc=tasystem::Globalconf::airSTP(0,f,1);
  cout << "omg:" << td::gc.getomg() << endl;
  inittrace(15);
  initothertrace(10,nltracer);


  // Create results dir, put all stuff in
  mkdir(dir,S_IRWXU | S_IRWXG);
  // Empty this directory
  system("rm results/*");

  td::Tube t(L,gp);


  int nsaves_per_period=50;
  int nr=0;
  d time=0;

  while(time<2*T){
    t.DoIntegration(dt);
    time=t.getTime();
    // cout << "Iteration done. Saving data...\n";
    if(true){
      // Create filename to store data to
    } // ti%10
  }
  return 0;
}



