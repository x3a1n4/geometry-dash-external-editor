#include "addon_manager.h"

#include <filesystem>
#include <iostream>

#include "API/gdee.h"

namespace gdee::python{

void AddonManager::InitializePython(){

    // append base gdee module
    PyImport_AppendInittab("gdee", &api::PyInit_gdee);

    // initialize python
    Py_Initialize();
}

namespace fs = std::filesystem;

// todo: load addons with other functions
void AddonManager::LoadAllAddons(){
    std::cout << "Loading addons" << std::endl;

    // Loop through all folders, find main.py file in each
    for (const auto& addonFolder : fs::directory_iterator(addon_path)) {
        if (addonFolder.is_directory()) {
            // Process subfolders
            std::string addonFolderPath = addonFolder.path().string();

            // Check if "main.py" exists in the subfolder
            std::string mainPyPath = addonFolderPath + "/main.py";
            if (fs::exists(mainPyPath)) {
                // if so, load it!
                Addon addon = Addon(mainPyPath);
            }
        }
    }
}

}