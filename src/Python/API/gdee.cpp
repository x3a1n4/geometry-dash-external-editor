#include "gdee.h"

#include <iostream>
#include <cstdio>

namespace gdee::python::api{

// note: static keyword outside of a class means that it's only visible within the file

static int numargs=0;
/* Return the number of arguments of the application command line */
static PyObject* gdee_numargs(PyObject *self, PyObject *args){
    if(!PyArg_ParseTuple(args, ":numargs"))
        return NULL;
    return PyLong_FromLong(numargs);
}

// code from https://stackoverflow.com/questions/5356773/python-get-string-representation-of-pyobject
static PyObject* gdee_print(PyObject *self, PyObject *args){
    PyObject_Print(args, stdout, Py_PRINT_RAW);
    //std::cout << args << std::endl;
    return NULL;
}

static PyMethodDef GdeeMethods[] = {
    {"numargs", gdee_numargs, METH_VARARGS,
     "Return the number of arguments received by the process. (test method)"},
    {"print", gdee_print, METH_VARARGS,
     "Print to the main console"}, //TODO: implement print function!
    {NULL, NULL, 0, NULL}
};

static PyModuleDef GdeeModule = {
    PyModuleDef_HEAD_INIT, "gdee", NULL, -1, GdeeMethods,
    NULL, NULL, NULL, NULL
};

PyObject* PyInit_gdee(){
    return PyModule_Create(&GdeeModule);
}

}