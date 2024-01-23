#pragma once

#define PY_SSIZE_T_CLEAN
#include <python3.11/Python.h>

namespace gdee::python::api{

PyObject* PyInit_gdee();

}