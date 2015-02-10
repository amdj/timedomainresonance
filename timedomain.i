%module timedomaineuler
%{
  #include "vtypes.h"
  #include "tube.h"
  #include "globalconf.h"
  SPOILNAMESPACE
    namespace td{
    extern tasystem::Globalconf gc;
  }
%}


typedef double d;
typedef unsigned us;

namespace tasystem{

  class Globalconf{
  public:
    d T0,p0;			/* Reference temperature and pressure (used to initialize a lot of variables. */
				// finite volume size, speed of sound,
				// deltax of volume
    d kappa;			// Artificial viscosity tuning factor,
    // typically between 0.25 and 0.75

    gases::Gas gas;

    Globalconf(us Nf=0,d freq=100,const string& gasstring="air",d T0=293.15,d p0=101325.0,d kappa=1.0,bool driven=true);
    const us& Nf() const;
    const us& Ns() const;
    static Globalconf airSTP(us Nf,d freq,d kappa=1.0);
    ~Globalconf(){TRACE(-5,"~Globalconf()");}
    bool isDriven() const;
    void setDriven(bool d);
    d getomg() const;
    d getfreq() const;
    d c0() const;
    d rho0() const;
    d deltanu0() const;
    vd omgvec;    
    void setNf(us);
    /* %rename set setNffreq */
    /* void set(us Nf,d freq);	// Set data for new frequency and */
    // number of samples
    void setomg(d omg);
    void setfreq(d freq);

    void setGas(const string& mat);
    const string& getGas() const;

    void setMass(d mass);
    d getMass() const;

    void show() const;
    //    void setgas(string g){ gas(g);}

  }; /* Class Globalconf */

} /* namespace tasystem */


namespace td{

  class SolutionAtGp {
  public:
    const d& rho() const;
    const d& m() const;
    const d& rhoE() const;
    d u() const;
    d ekin() const;
    d estat() const;
    d p() const;

    d Cflux() const;
    d Mflux() const;
    d Eflux() const;
    SolutionAtGp();
    ~SolutionAtGp(){}
    void setData(d rho,d m=0,d rhoE=0);
  };
  class SolutionInstance{
  public:
    SolutionInstance(int gp);
    ~SolutionInstance(){}
    d getTime() const;
    void setTime(d t);
    void setData(us i,SolutionAtGp& sol);
    SolutionAtGp& get(us i);
    void setrho(d rho);
  };

  tasystem::Globalconf gc;

  class Tube{
  public:
    Tube(double L,int gp);
    ~Tube(){}
    SolutionInstance& getSol();
    void setSol(const SolutionInstance& sol);
    void DoIntegration(d dt,int n=1);
    d getTime();
  };
}

