%module timedomaineuler
%{
  #define PY_ARRAY_UNIQUE_SYMBOL npy_array_api
  /* #define NO_IMPORT_ARRAY */
  #define SWIG_FILE_WITH_INIT
  #include <cerrno>
  #include <cstdlib>
  #include "vtypes.h"
  #include "arma_numpy.h"
  #include "tube.h"

  #include "globalconf.h"
  SPOILNAMESPACE
    namespace td{
    extern tasystem::Globalconf gc;
  }
%}

/* Call import_array() on loading module*/
%init%{
  cout << "Import array called\n";
  import_array();
%}

// A better way is the following
// Convert from numpy to vd and vice versa
class vd{
 public:
  virtual ~vd();
};

%typemap(in) const vd& INPUT {
  PyArrayObject* arr = (PyArrayObject*) PyArray_FROM_OTF($input, NPY_DOUBLE, NPY_IN_ARRAY);
  if(arr==NULL)
    return NULL;
  int ndims=PyArray_DIM(arr,0);
  if(ndims!=1){
    // PyErr_SetString(PyExc_TypeError,"Number of dimensions not equal to 1");
    return NULL;
  }
  $1= vd_from_npy(arr);
}
%typemap(out) vd {
  $result=npy_from_vd($1);
}
%typemap(out) vd& {
  const vd& res=*$1;
  $result=npy_from_vd(res);
}
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

  class SolutionInstance{
  public:
    SolutionInstance(int gp,d rho=1.2);
    ~SolutionInstance(){}
    vd p() const;
    vd u() const;
    const vd& rho() const;
    const vd& m() const;
    const vd& rhoE() const;
    d getTime() const;
    void setTime(d t);
    void setrho(d rho);
  };

  tasystem::Globalconf gc;

  class Tube {
  public:
    d dx, L;              // Grid spacing, total length
    int gp;               // Number of gridpoints
    SolutionInstance sol; // Solutions at time instances
    d t = 0;              // Current time
    d pleft(d t);         // Compute pressure bc
    virtual void Integrate(d dt) = 0;

  public:
    Tube(double L, int gp) throw(int);
    virtual ~Tube() {}
    SolutionInstance &getSol();
    void setSol(const SolutionInstance &sol);
    void DoIntegration(d dt, int n = 1);
    d getTime() { return t; }
  };
  class TubeLF:public Tube{
    virtual void Integrate(d dt);
  public:
    TubeLF(d L,int gp);
  };
}

