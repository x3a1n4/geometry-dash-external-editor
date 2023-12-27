#include "AddonManager.h"
#include <python3.11/Python.h>
#include <string.h>

class AddonManager {
	// TODO: get proper build path
	public static char[] filepath = "";
	public static 

	public static int loadPythonFiles() {
		// load all files, and add them to the loaded addons
		Py_Initialize();
	}

	public static int registerPythonFiles() {
		// Loop through all top-level python files in folders, and call their register() func
	}

	public static int unregisterPythonFiles() {
		// Call all unregister() funcs
	}
};

