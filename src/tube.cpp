#include "tube.h"

namespace td{
  tasystem::Globalconf gc;

  d Tube::pleft(d t){
    d pleft=std::sin(gc.getomg()*t);
    cout << "t:"<< t<<endl;
    cout << "omg:" << gc.getomg()<< endl;
    // cout << "pleft:"<< pleft<<endl;
    return pleft;

  }
  Tube::Tube(d L,int gp):
    L(L),
    gp(gp),
    sol(SolutionInstance(gp))  {

    TRACE(15,"Tube::Tube()");
    dx=L/(gp-1);
    VARTRACE(15,gp);
    sol.setrho(gc.rho0());
  }

  void Tube::DoIntegration(d dt,int n){
    TRACE(14,"Tube::DoIntegration()");
    int integrations=0;
    while(integrations<n){
      Integrate(dt);
      integrations++;
    }
  }
  void Tube::Integrate(d dt){

    // Define new time
    d newt=t+dt;

    // Define new solutioninstance
    SolutionInstance newsol(gp);
    newsol.setTime(newt);
    SolutionAtGp newsolgp;
    d rho,m,rhoE;

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
      newsolgp.setData(rho,m,rhoE);
      newsol.setData(i,newsolgp);

    } // Leftmost node
    // TRACE(15,"leftmost done");
    // Inner nodes
    for(i=1;i<gp-1;i++){
      SolutionAtGp& im1=sol.get(i-1);
      SolutionAtGp& ip1=sol.get(i+1);
      d lambda=dt/(2*dx);
      rho=0.5*(im1.rho()+ip1.rho())-lambda*(ip1.Cflux()-im1.Cflux());
      m=0.5*(im1.m()+ip1.m())-lambda*(ip1.Mflux()-im1.Mflux());
      rhoE=0.5*(im1.rhoE()+ip1.rhoE())-lambda*(ip1.Eflux()-im1.Eflux());

      newsolgp.setData(rho,m,rhoE);
      newsol.setData(i,newsolgp);
      
    } // for over all gridpoints in mid
    {
      i=gp-1;
      SolutionAtGp& im1=sol.get(i-1);
      SolutionAtGp& ip0=sol.get(i);

      d la=dt/(dx);
      rho=ip0.rho()-la*(0-im1.Cflux());
      m=0;
      rhoE=ip0.rhoE()-la*(0-im1.Eflux());

      newsolgp.setData(rho,m,rhoE);
      newsol.setData(i,newsolgp);
    }

    // Finally, update time and solution
    sol=newsol;
    t=newt;
  }

} // namespace td
