#pragma once

#include <python3.11/Python.h>
#include <string>

class GdeeModule {
public:
    static PyObject* PyInit_GDEE(void);

    static const std::string moduleName;
private:
    static PyModuleDef Module;

    static PyMethodDef Methods[];

    static PyObject* test_function(PyObject* self, PyObject* args);
};

const std::string GdeeModule::moduleName{ "gdee" }; // can't initialize in class, not sure why but VS yells at me