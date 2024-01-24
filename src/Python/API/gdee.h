#pragma once

#define PY_SSIZE_T_CLEAN
#include <Python.h>

namespace gdee::python::api{

PyObject* PyInit_gdee();

}