#pragma once

#include <python3.11/Python.h>
#include <string>
#include <string_view>

// Generic addon class
class Addon {
public:
	Addon(std::string_view path);
	std::string addonPath;

	void registerAddon();
	void unregisterAddon();

private:
	void callAddonFunc(PyObject* pFunc);

	PyObject* pModule{};

	PyObject* registerPFunc{};
	PyObject* unregisterPFunc{};
};