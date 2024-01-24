#pragma once

#include <vector>
#include <string>
#include <filesystem>

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "generic_addon.h"

namespace gdee::python{

class AddonManager{
public:
    static void Init();

    static std::filesystem::path GetAddonDirectoryPath();

private:
    // Initialize the python environment (mainly loading modules)
    static void InitializePython();

    // Iterate through the addon path, and load all top-level .py files named "main"
    static void LoadAllAddons();

    // Just figuring things out here, methods should include
    // - A way to register, unregister ALL addons (for startup)
    // - A way to register, unregister a single addon (for coding)
    static void RegisterAllAddons();
    static void UnregisterAllAddons();

    static void RegisterAddon(Addon addon);
    static void UnregisterAddon(Addon addon);

    static std::vector<Addon> loaded_addons;
};

}