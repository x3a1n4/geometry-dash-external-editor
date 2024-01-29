#include "addon_manager.h"

#include <iostream>

#include "API/gdee.h"
#include "Windows.h"

namespace gdee::python{

std::vector<Addon> AddonManager::loaded_addons; // Why do I need to put this here?

namespace fs = std::filesystem;

std::filesystem::path AddonManager::GetAddonDirectoryPath(){
    char exe_path[MAX_PATH];
    GetModuleFileName(NULL, exe_path, MAX_PATH); // NOTE: only works for windows. 
    fs::path addon_path = fs::path(exe_path).parent_path().append("Addons");

    if(!fs::is_directory(addon_path)){
        throw "Error: Addon folder not found";
    }
    
    return addon_path;

}

void AddonManager::InitializePython(){

    // append base gdee module
    PyImport_AppendInittab("gdee", &api::PyInit_gdee);

    // initialize python
    Py_Initialize();
}

// todo: load addons with other functions
void AddonManager::LoadAllAddons(){
    // https://stackoverflow.com/questions/10675054/how-to-import-a-module-in-python-with-importlib-import-module
    std::cout << "Loading addons from folder " << GetAddonDirectoryPath() << std::endl;

    // Loop through all folders, find main.py file in each
    for (const auto& addonFolder : fs::directory_iterator(GetAddonDirectoryPath())) {
        if (addonFolder.is_directory()) {

            // Check if "main.py" exists in the subfolder
            fs::path mainPyPath = addonFolder.path() / "main.py";
            if (fs::exists(mainPyPath)) {
                // if so, load it!
                std::cout << "Loading addon at " << mainPyPath << std::endl;

                // The module name is just [the folder name] + "main"
                std::string module_name = addonFolder.path().filename().string() + ".main";

                Addon addon = Addon(module_name);
                
                loaded_addons.push_back(addon);
            }
        }
    }
}

void AddonManager::RegisterAddon(Addon addon){
    // Call register function
    if(!addon.is_registered){
        addon.Register();
    }
}

void AddonManager::UnregisterAddon(Addon addon){
    // Call unregister function
    if(addon.is_registered){
        addon.Unregister();
    }
}

void AddonManager::RegisterAllAddons(){
    for(Addon addon : loaded_addons){
        RegisterAddon(addon);
    }
}

void AddonManager::UnregisterAllAddons(){
    for(Addon addon : loaded_addons){
        UnregisterAddon(addon);
    }
}

void AddonManager::Init(){
    InitializePython();
    LoadAllAddons();
    RegisterAllAddons();
}



}