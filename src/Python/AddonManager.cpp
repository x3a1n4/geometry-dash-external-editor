#include "AddonManager.h"

#include "Addon.h"
// TODO: including headers as directories like this is bad practice (https://www.learncpp.com/cpp-tutorial/header-files/), figure out ...eventually
#include "Module/gdee.h"

#include <python3.11/Python.h>

#include <string>
#include <string_view>
#include <filesystem>

namespace fs = std::filesystem;

#define PY_SSIZE_T_CLEAN

class AddonManager {
public:
    // TODO: get proper  path
	const std::string_view addonsPath = "Addons"; 

    // Load addons, do this on startup!
    // TODO: strings shouldn't be passed by value (https://www.learncpp.com/cpp-tutorial/introduction-to-stdstring/)
    // Use std::string_view
	int loadAllAddons(std::string_view addonsParentPath) {
        // Initialize
        PyImport_AppendInittab("gdee", &GdeeModule::PyInit_GDEE); // Append gdee module
		Py_Initialize();

        // Loop through all folders, find main.py file in each
        // TODO: simply run all files named "main.py". This can be changed later
        for (const auto& addonFolder : fs::directory_iterator(addonsParentPath)) {
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

private:
    // reload addon by unregistering it, and then making a new addon from its path (path is a folder, and should not change)
    // can also reload all addons
};

