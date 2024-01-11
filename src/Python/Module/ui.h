#pragma once

#include "ui.h"

#include <python3.11/Python.h>

// put in header
class UIModule {
public:
	typedef struct {
		PyObject_HEAD // No semicolon after this, it's a macro!
		int number_for_testing_purposes;
		/* Type-specific fields go here. */
	} UI_Object;

	static void preRender(UI_Object* frame);
	static void render(UI_Object* frame);
	static void postRender(UI_Object* frame);

private:
	static PyTypeObject UI_Type;
	static PyMethodDef UI_Type_Methods[];
};