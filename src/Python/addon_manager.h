#pragma once

#include <vector>
#include <string>

#define PY_SSIZE_T_CLEAN
#include <python3.11/Python.h>

#include "generic_addon.h"

namespace gdee::python{

class AddonManager{
public:
    // Initialize the python environment (mainly loading modules)
    static void InitializePython();

    // Iterate through the addon path, and load all top-level .py files named "main"
    static void LoadAllAddons();

    // Just figuring things out here, methods should include
    // - A way to register, unregister ALL addons (for startup)
    // - A way to register, unregister a single addon (for coding)
    static constexpr const char* addon_path{"Addons"};

private:
    static std::vector<Addon> loaded_addons;
};

}