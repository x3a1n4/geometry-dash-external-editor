#include "addon_manager.h"

#include "Module/gdee.h"

namespace gdee::python{

void AddonManager::InitializePython(){

    // append base gdee module
    PyImport_AppendInittab("gdee", &module::PyInit_gdee);

    // initialize python
    Py_Initialize();
}

// todo: load addons with other functions

}