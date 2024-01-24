#include "addon_manager.h"

#include <iostream>

#include "API/gdee.h"

namespace gdee::python{

std::vector<Addon> AddonManager::loaded_addons; // Why do I need to put this here?

namespace fs = std::filesystem;
std::filesystem::path AddonManager::GetAddonDirectoryPath(){
    fs::path addon_path = fs::path(__FILE__).parent_path().parent_path().parent_path().append("Addons");

    // check to make sure that directory exists
    
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
    std::cout << "Loading addons from folder " << GetAddonDirectoryPath() << std::endl;

    // Loop through all folders, find main.py file in each
    // FIXME: verify addon folder exists
    for (const auto& addonFolder : fs::directory_iterator(GetAddonDirectoryPath())) {
        if (addonFolder.is_directory()) {
            // Process subfolders
            // NOTE: don't need a string here, could keep as fs::
            std::string addonFolderPath = addonFolder.path().string();

            // Check if "main.py" exists in the subfolder
            std::string mainPyPath = addonFolderPath + "\\main.py";
            if (fs::exists(mainPyPath)) {
                // if so, load it!
                std::cout << "Loading addon at " << mainPyPath << std::endl;
                Addon addon = Addon(mainPyPath);
                
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