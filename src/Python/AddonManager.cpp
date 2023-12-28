#include "AddonManager.h"

#include "Addon.h"

#include <python3.11/Python.h>

#include <string>
#include <filesystem>

namespace fs = std::filesystem;

class AddonManager {
public:
    // A couple thoughts:
    // Well, blender has you make a class that extends, say, bpy.types.Operator,
    // And you register that operator class with bpy.utils.register_class()
    // 
    // So this is going to be bulky. I'll try to set it up for now, but I think it will be beneficial
    // If register and unregister are the ONLY two functions
    // 
    // And otherwise, you register, say, windows and objects by making classes that extend gdee.genericUI or whatever.
    // 
    // TODO: get proper  path
	const std::string addonsPath = "Addons"; 

    // Load addons, do this on startup!
	int loadAllAddons(std::string addonsParentPath) {
		// get all files
		Py_Initialize(); // Initialize

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

