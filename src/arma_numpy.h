#pragma once
#ifndef ARMA_NUMPY_H
#define ARMA_NUMPY_H
#include <Python.h>
#include <numpy/arrayobject.h>
#include "vtypes.h"
SPOILNAMESPACE
vd vd_from_npy(PyArrayObject const * const);
PyObject* npy_from_vd(const vd& armavec);



#endif // ARMA_NUMPY_H
