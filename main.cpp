#include "tube.h"
#include "tracer.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <boost/program_options.hpp>
#include <ctime>
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

  d f=85.785;
  int loglevel=20;

  po::options_description desc("Allowed options");
  desc.add_options()
    ("help", "Produce help message")
    ("frequency",po::value<d>(&f)->default_value(100))
    ;
  d T=1/f;
  d L=1;
  us gp=500;

  d dx=L/(gp-1);                    // One left and right gp, so
  d CFL=0.95;
  // This is questionable
  d dt=min(CFL*dx/gc.c0(),T/50);
  cout << "dt:" << dt <<"\n";
  cout << "dx:" << dx <<"\n";

  td::gc=tasystem::Globalconf::airSTP(0,f,1);
  cout << "omg:" << td::gc.getomg() << endl;
  inittrace(loglevel);
  initothertrace(loglevel,nltracer);


  // Create results dir, put all stuff in
  mkdir(dir,S_IRWXU | S_IRWXG);
  // Empty this directory

  td::Tube t(L,gp);


  int nsaves_per_period=50;

  int approx_instances_per_period=round(T/dt);
  if(nsaves_per_period>approx_instances_per_period){ // Not good..
    WARN("Error: to many saves for number of time instances available. Try adjusting nsaves_per_period Exiting..");
    exit(192);
  }

  
  d time=0;

  us loopnr=1;
  us savenr=0;
  us saves_per_period=20;

  d tbetweensaves=T/saves_per_period;

  d tlastsave=0;

  std::stringstream pfilename,ufilename;
  pfilename << dir;  ufilename << dir;  
  pfilename << "/p.dat";
  ufilename << "/u.dat";
  std::ofstream p(pfilename.str());
  std::ofstream u(ufilename.str());
  p   << "#Pressure data vs gridpoint. gp=" << gp << "\n";
  u   << "#Velocity data vs gridpoint. gp=" << gp << "\n";

  t.getSol().save(p,data::p);
  t.getSol().save(u,data::u);
  const clock_t begin_time = std::clock();  
  while(time<180*T){
    t.DoIntegration(dt);
    time=t.getTime();

    if(time-tlastsave>tbetweensaves){
      tlastsave=time;
      savenr++;
      t.getSol().save(p,data::p);
      t.getSol().save(u,data::u);
      cout << "Saving for t= " << time << " s.\n";
    } // ti%10
    loopnr++;
  }
  d comptime=std::clock()-begin_time;
  p << "#Total time required to obtain solution: " << comptime/CLOCKS_PER_SEC <<" \n";
  return 0;
}



