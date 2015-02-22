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

void Tube::DoIntegration(d dt, int maxnr) {
  TRACE(14, "Tube::DoIntegration()");
  int intnr = 0;
  for (intnr=0; intnr < maxnr; intnr++) {
    sol=Integrate(dt);		// Update solution  
  }
}
SolutionInstance TubeLF::Integrate(d dt) {
  // Integrate using Lax-Friedrich method
  d t=sol.getTime();
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
    rho.subvec(1,gp-2)+=-lambda*(Cflux.tail(gp-2) -Cflux.head(gp-2));
  
    m.subvec(1,gp-2)=0.5*(oldm.head(gp-2) + oldm.tail(gp-2));
    m.subvec(1,gp-2)+=-lambda*(Mflux.tail(gp-2) -Mflux.head(gp-2));

    rhoE.subvec(1,gp-2)=0.5*(oldrhoE.head(gp-2) + oldrhoE.tail(gp-2));
    rhoE.subvec(1,gp-2)+=-lambda*(Eflux.tail(gp-2) -Eflux.head(gp-2));
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

  return newsol;
}
  SolutionInstance TubeMCM::Integrate(d dt){ // Integrate using
					     // MacCormack method
    d t=sol.getTime();
    d newt=t+dt;

    d lambda=dt/dx;

    SolutionInstance predictor(gp);
    {				// Predictor step
      const vd& oldrho=sol.rho();
      const vd& oldm=sol.m();
      const vd& oldrhoE=sol.rhoE();
    
      vd& prho=predictor.rho_ref();
      vd& pm=predictor.m_ref();
      vd& prhoE=predictor.rhoE_ref();
      // Fluxes from previous solution
      vd Cflux=sol.Cflux();
      vd Mflux=sol.Mflux();
      vd Eflux=sol.Eflux();

      // Density
      prho.tail(gp-1)=oldrho.tail(gp-1)
	-lambda*(Cflux.tail(gp-1)-Cflux.head(gp-1));
      // The first element
      prho(0)=oldrho(0)-lambda*(Cflux(1)-Cflux(0));

      // Momentum
      d oldu0=oldm(0)/oldrho(0);
      d momfluxl = pow(oldm(0), 2)/oldrho(0) + pleft(t);

      pm.tail(gp-1)=oldm.tail(gp-1)
	-lambda*(Mflux.tail(gp-1)-Mflux.head(gp-1));
      // The first element
      pm(0)=oldm(0)-lambda*(Mflux(1)-momfluxl);
      pm(gp-1)=0;

      // Energy
      prhoE.tail(gp-1)=oldrhoE.tail(gp-1)
	-lambda*(Eflux.tail(gp-1)-Eflux.head(gp-1));
      // The first element
      prhoE(0)=oldrhoE(0)-lambda*(Eflux(1)-Eflux(0));

    }
    SolutionInstance corrector(gp);
    // Temp test hack:
    corrector=predictor;
    corrector.setTime(newt);

    return corrector;
  }					     // Integrate(dt)
} // namespace td
