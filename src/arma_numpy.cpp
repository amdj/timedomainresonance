// arma_numpy.cpp
//
// last-edit-by: J.A. de Jong 
// 
// Description:
//
//////////////////////////////////////////////////////////////////////
#define PY_ARRAY_UNIQUE_SYMBOL npy_array_api
#define NO_IMPORT_ARRAY
#include "arma_numpy.h"

// Annes conversion functions. In a later stage they have to be
// generalized for arrays of arbitrary dimensions

PyObject *npy_from_vd(const vd &in) {
  long int size = in.size();
  npy_intp dims[1] = {size};

  // This code should be improved massively?
  if (size == 0) {
    std::cout << "Size is zero!\n";
    return NULL;
  }
  PyArrayObject *array =
      (PyArrayObject *)PyArray_SimpleNew(1, dims, NPY_DOUBLE);
  if (array == NULL) {
    return NULL;
  }
  double *pydat = (double *)PyArray_DATA(array);
  mempcpy(pydat, in.memptr(), size * sizeof(double));

  return PyArray_Return(array);
}
vd vd_from_npy(const PyArrayObject *const in) {

  npy_intp size=PyArray_DIMS(in)[0]; // Extract first 
  double *pydata = (double *)PyArray_DATA(in);
  vd result(size);
  memcpy(result.memptr(),pydata,size*sizeof(double));
  return result;
}
