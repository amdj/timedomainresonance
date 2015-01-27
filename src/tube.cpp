#include "tube.h"

namespace td{

  // Definition of a Globalconf in this namespace. Is initialized in main()
  tasystem::Globalconf gc;

  d Tube::pleft(d t){
    d pleft=std::sin(gc.getomg()*t);
    // cout << "t:"<< t<<endl;
    // cout << "pleft:"<< pleft<<endl;
    return pleft;

  }
  Tube::Tube(d L,int gp): L(L),gp(gp),sol(SolutionInstance(0,gp))  {
    TRACE(15,"Tube::Tube()");
    dx=L/(gp-1);
    VARTRACE(15,gp);
    sol.setrho(gc.rho0());
  }

  void Tube::DoIntegration(d dt){
    TRACE(14,"Tube::DoIntegration()");

    // Define new time
    d newt=t+dt;

    // Define new solutioninstance
    SolutionInstance newsol=sol;

    SolutionAtGp newsolgp;
    d rho,m,rhoE;

    newsol.setTime(newt);

    int i=0;
    // Left boundary
    {
      SolutionAtGp& ip1=sol.get(i+1);
      SolutionAtGp& ip0=sol.get(i);
      d la=dt/(dx);
      rho=ip0.rho()-la*(ip1.Cflux()-ip0.Cflux());
      d momfluxl=ip0.rho()*pow(ip0.u(),2)+pleft(t);
      m=ip0.m()-la*(ip1.Mflux()-momfluxl);
      rhoE=ip0.rhoE()-la*(ip1.Eflux()-ip0.Eflux());
      // rhoE=ip0.rhoE()-la*(ip1.Eflux()-.rhoE()*ip0.u()-ip0.u()*(gc.p0+pleft(t)));
      newsolgp.set(rho,m,rhoE);
      // cout << "pleft: " << pleft(t) <<"\n";
      // cout << "pleft: " << newsolgp.p() <<"\n";
      newsol.set(i,newsolgp);

    } // Leftmost node
    // TRACE(15,"leftmost done");
    // Inner nodes
    for(i=1;i<gp-2;i++){
      SolutionAtGp& im1=sol.get(i-1);
      SolutionAtGp& ip1=sol.get(i+1);
      d lambda=dt/(2*dx);
      rho=0.5*(im1.rho()+ip1.rho())-lambda*(ip1.Cflux()-im1.Cflux());
      m=0.5*(im1.m()+ip1.m())-lambda*(ip1.Mflux()-im1.Mflux());
      rhoE=0.5*(im1.rhoE()+ip1.rhoE())-lambda*(ip1.Eflux()-im1.Eflux());

      newsolgp.set(rho,m,rhoE);
      newsol.set(i,newsolgp);
      
    } // for over all gridpoints in mid
    {
      i++;
      SolutionAtGp& im1=sol.get(i-1);
      SolutionAtGp& ip0=sol.get(i);

      d la=dt/(dx);
      rho=ip0.rho()-la*(0-im1.Cflux());
      m=0;
      rhoE=ip0.rhoE()-la*(0-im1.Eflux());

      newsolgp.set(rho,m,rhoE);
      newsol.set(i,newsolgp);
    }

    // Finally, update time and solution
    sol=newsol;
    t=newt;
  }




} // namespace td
