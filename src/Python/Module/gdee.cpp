#include "gdee.h"

#include <python3.11/Python.h>
#include <string>

#define PY_SSIZE_T_CLEAN

// Implement python module
// from https://docs.python.org/3/extending/embedding.html
PyObject* GdeeModule::PyInit_GDEE(void) {
    return PyModule_Create(&Module);
}

// Notes from https://docs.python.org/3/c-api/module.html#c.PyModuleDef
// We set the name (gdee) and the methods, note that we can set the module
PyModuleDef GdeeModule::Module = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "gdee",
    .m_doc = "GDEE Module",
    .m_size = -1,
    .m_methods = Methods,
};

// Define methods available here!
PyMethodDef GdeeModule::Methods[]{
    {"test", test_function, METH_VARARGS,
     "Return the number of arguments received by the process."},
    {"test", test_function, METH_VARARGS,
     "Return the number of arguments received by the process."},
    {NULL, NULL, 0, NULL} // zero function
    };

    // Define a test function
    // This will be expanded later
PyObject* GdeeModule::test_function(PyObject* self, PyObject* args){
    return PyUnicode_FromString("Hello World!");
};