#include "tube.h"

TRACETHIS

namespace td {
tasystem::Globalconf gc;

d Tube::pleft(d t) {
  d pleft = std::sin(gc.getomg() * t);
  // cout << "t:" << t << endl;
  // cout << "omg:" << gc.getomg() << endl;
  // cout << "pleft:"<< pleft<<endl;
  return pleft;
}
  Tube::Tube(d L, int gp) throw(int) : L(L), gp(gp), sol(SolutionInstance(gp)) {
  TRACE(15, "Tube::Tube()");
  dx = L / (gp - 1);
  if(gp<5)
    throw 1;
  VARTRACE(15, gp);
  sol.setrho(gc.rho0());
}

void Tube::DoIntegration(d dt, int n) {
  TRACE(14, "Tube::DoIntegration()");
  int integrationnumber = 0;
  while (integrationnumber < n) {
    Integrate(dt);
    integrationnumber++;
  }
}
void TubeLF::Integrate(d dt) {
  // Integrate using Lax-Friedrich method
  d newt = t + dt;
  // Define new solutioninstance
  SolutionInstance newsol(gp);
  newsol.setTime(newt);

  const vd& oldrho=sol.rho();
  const vd& oldm=sol.m();
  const vd& oldrhoE=sol.rhoE();

  vd& rho=newsol.rho_ref();
  vd& m=newsol.m_ref();
  vd& rhoE=newsol.rhoE_ref();

  // Fluxes from previous solution
  vd Cflux=sol.Cflux();
  vd Mflux=sol.Mflux();
  vd Eflux=sol.Eflux();

  {  // Left boundary
    d la = dt/dx;
    rho(0) = oldrho(0);
    rho(0)+=-la*(Cflux(1)-Cflux(0));
    d oldu0=oldm(0)/oldrho(0);
    // std::cout << "oldu:"<< oldu0 << std::endl;
    d momfluxl = pow(oldm(0), 2)/oldrho(0) + pleft(t);
    m(0) = oldm(0);
    m(0)+=-la*(Mflux(1)-momfluxl);
    rhoE(0) = oldrhoE(0);
    rhoE(0)+=-la*(Eflux(1)-Eflux(0));
  } //  End left boundary

  {				// Inner nodes
    d lambda = dt/(2*dx);
    rho.subvec(1,gp-2)=0.5*(oldrho.head(gp-2) + oldrho.tail(gp-2));
    rho.subvec(1,gp-2)+=-lambda*(Cflux.head(gp-2) -Cflux.tail(gp-2));
  
    m.subvec(1,gp-2)=0.5*(oldm.head(gp-2) + oldm.tail(gp-2));
    m.subvec(1,gp-2)+=-lambda*(Mflux.head(gp-2) -Mflux.tail(gp-2));

    rhoE.subvec(1,gp-2)=0.5*(oldrhoE.head(gp-2) + oldrhoE.tail(gp-2));
    rhoE.subvec(1,gp-2)+=-lambda*(Eflux.head(gp-2) -Eflux.tail(gp-2));
  } // End inner nodes

  {				// Right boundary
    int i = gp - 1;
    d la = dt/dx;
    rho(i) = oldrho(i);
    rho(i)+=-la*(0-Cflux(i-1));
    m(i) = 0;
    rhoE(i) = oldrhoE(i);
    rhoE(i)+=-la*(0-Eflux(i-1));
  } // End right boundary

  // Finally, update time and solution
  sol = newsol;
  t = newt;
}

} // namespace td
