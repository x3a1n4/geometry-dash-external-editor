#include "gdee.h"

namespace gdee::python::api{

// note: static keyword outside of a class means that it's only visible within the file

static int numargs=0;
/* Return the number of arguments of the application command line */
static PyObject* gdee_numargs(PyObject *self, PyObject *args){
    if(!PyArg_ParseTuple(args, ":numargs"))
        return NULL;
    return PyLong_FromLong(numargs);
}

static PyMethodDef GdeeMethods[] = {
    {"numargs", gdee_numargs, METH_VARARGS,
     "Return the number of arguments received by the process. (test method)"},
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