#pragma once

#define PY_SSIZE_T_CLEAN
#include <python3.11/Python.h>
#include <string>

namespace gdee::python{

class Addon{
public:
    Addon(std::string file_path);
    ~Addon();

    bool operator==(const Addon &a);

    // Calling these functions on an Addon should call the associated python functions
    int Register();
    int Unregister();
private:
    // Save original file path of addon
    std::string python_file_path;

    // store internal python pointers
    // module: contains base file
    PyObject* py_module;

    // variable containing the addon info (may go unused)
    PyObject* py_addon_info;

    // register and unregister functions are called when enabling, disabling addons
    // Named in python as register(), unregister() respectively
    PyObject* py_register_function;
    PyObject* py_unregister_function;
};

}