#include "generic_addon.h"

// generic addon class
namespace gdee::python{

Addon::Addon(std::string file_path){
    python_file_path = file_path;
    // find all relevant addon properties, and save them to class 
    PyObject *py_name = PyUnicode_DecodeFSDefault(file_path.c_str());

    py_module = PyImport_Import(py_name);
    Py_DECREF(py_name);

    if (py_module != NULL) {
        // get functions
        py_register_function = PyObject_GetAttrString(py_module, "register");
        py_unregister_function = PyObject_GetAttrString(py_module, "unregister");
    }
}

Addon::~Addon(){
    // decrease references to all objects (freeing their memory)
    Py_XDECREF(py_register_function);
    Py_XDECREF(py_unregister_function);

    Py_XDECREF(py_addon_info);

    Py_XDECREF(py_module);
}

// Simply equate addons based on file path name
bool Addon::operator==(const Addon &a){
    return python_file_path == a.python_file_path;
}

// Call register() function on addon's python file
int Addon::Register(){
    if (py_register_function && PyCallable_Check(py_register_function)) {
        // Call function, more error handling likely required
        PyObject_CallObject(py_register_function, nullptr);
        return 0;
    }
    return 1;
}

// Same as, but for unregister()
int Addon::Unregister(){
    if (py_unregister_function && PyCallable_Check(py_unregister_function)) {
        PyObject_CallObject(py_unregister_function, nullptr);
        return 0;
    }
    return 1;
}

}