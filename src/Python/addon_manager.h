#pragma once

#include <vector>

#define PY_SSIZE_T_CLEAN
#include <python3.11/Python.h>

#include "generic_addon.h"

namespace gdee::python{

class AddonManager{
public:
    static void InitializePython();

private:
    static std::vector<Addon> loaded_addons;
};

}