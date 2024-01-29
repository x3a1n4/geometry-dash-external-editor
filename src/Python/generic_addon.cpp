#include "generic_addon.h"

#include <iostream>

// generic addon class
namespace gdee::python{

Addon::Addon(std::string module){
    python_module = module;
    // find all relevant addon properties, and save them to class 
    PyObject *py_name = PyUnicode_DecodeFSDefault(module.c_str());

    py_module = PyImport_Import(py_name);
    Py_DECREF(py_name);

    if (py_module != NULL) {
        // get functions, note if the function does not exist then it crashes!
        // TODO: add proper error handling, logging
        if(PyObject_HasAttrString(py_module, "register")){
            py_register_function = PyObject_GetAttrString(py_module, "register");
        }else{
            throw "Error! Addon " + python_module + " has no register() function defined";
        }

        if(PyObject_HasAttrString(py_module, "unregister")){
            py_unregister_function = PyObject_GetAttrString(py_module, "unregister");
        }else{
            throw "Error! Addon " + python_module + " has no unregister() function defined";
        }
        
        
    }
}

Addon::~Addon(){
    // TODO: fix memory leakage
}

void Addon::Free(){
    Py_XDECREF(py_register_function);
    Py_XDECREF(py_unregister_function); // make sure it exists!

    Py_XDECREF(py_addon_info);

    Py_XDECREF(py_module);
}

// Simply equate addons based on file path name
bool Addon::operator==(const Addon &a){
    return python_module == a.python_module;
}

// Call register() function on addon's python file
int Addon::Register(){
    // FIXME: Read Access violation
    if (py_register_function && PyCallable_Check(py_register_function)) {
        // Call function, more error handling likely required
        PyObject_CallObject(py_register_function, nullptr);

        is_registered = true;
        return 0;
    }
    return 1;
}

// Same as, but for unregister()
int Addon::Unregister(){
    if (py_unregister_function && PyCallable_Check(py_unregister_function)) {
        PyObject_CallObject(py_unregister_function, nullptr);

        is_registered = false;
        return 0;
    }
    return 1;
}

}