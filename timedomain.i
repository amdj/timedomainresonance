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

%include "gc.i"

namespace td{

  tasystem::Globalconf gc;

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
  // %feature("abstract") Tube;	// Define Tube abstract
 class Tube {
 protected:
    virtual SolutionInstance Integrate(d dt)=0;
  public:
    Tube(double L, int gp) throw(int);
    virtual ~Tube() {}
    SolutionInstance &getSol();
    void setSol(const SolutionInstance &sol);
    void DoIntegration(d dt, int n = 1);
    d getTime() { return t; }
  };
  class TubeLF:public Tube{
  protected:
    virtual SolutionInstance Integrate(d dt);
  public:
    TubeLF(d L,int gp);
  };
  class TubeMCM:public Tube{
  protected:
    virtual SolutionInstance Integrate(d dt);
  public:
    TubeMCM(d L,int gp);
  };
}

