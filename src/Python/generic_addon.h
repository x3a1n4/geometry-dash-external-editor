#pragma once

#define PY_SSIZE_T_CLEAN
#include <Python.h> // FIXME: you don't need to include the full path, just use Python.h! MSVC can't hurt you here.
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

    // Save whether addon is currently registered
    bool is_registered = false;

    // Save original file path of addon
    std::string python_file_path;
private:
    // store internal python pointers
    // module: contains base file
    PyObject* py_module{};

    // variable containing the addon info (may go unused)
    PyObject* py_addon_info{};

    // register and unregister functions are called when enabling, disabling addons
    // Named in python as register(), unregister() respectively
    PyObject* py_register_function{};
    PyObject* py_unregister_function{};
};

}