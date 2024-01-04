#pragma once

#include "ui.h"

#include <python3.11/Python.h>

// put in header
class UIModule {
public:
	static void preRender();
	static void render();
	static void postRender();

private:
	static PyTypeObject UI_Type;
	static PyMethodDef UI_Type_Methods[];
};