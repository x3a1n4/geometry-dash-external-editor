#include "Addon.h"

// Generic addon class

// load addon from path to main.py file
Addon::Addon(std::string_view path) {
	addonPath = path; // save path

	PyObject* pName = PyUnicode_DecodeFSDefault(path.data());

	pModule = PyImport_Import(pName); // load the module
	Py_DECREF(pName);

	if (pModule != NULL) {
		// load desired functions
		registerPFunc = PyObject_GetAttrString(pModule, "register");
		unregisterPFunc = PyObject_GetAttrString(pModule, "unregister");
	}
}

void Addon::registerAddon() {
	callAddonFunc(registerPFunc);
}

void Addon::unregisterAddon() {
	callAddonFunc(unregisterPFunc);

	// Clean up python objects
	Py_XDECREF(registerPFunc);
	Py_XDECREF(unregisterPFunc);

}
void Addon::callAddonFunc(PyObject* pFunc) {

	PyObject* pArgs = nullptr;
	// https://docs.python.org/3/extending/embedding.html#extending-embedded-python
	// Check if it exists, and is callable
	if (pFunc && PyCallable_Check(pFunc)) {
		// Note: can pass args if needed
		// Although python will be able to access regardless through the extension
		PyObject_CallObject(pFunc, pArgs); // Call register()
	}

	// Clean up
	// Py_XDECREF(pFunc);
}