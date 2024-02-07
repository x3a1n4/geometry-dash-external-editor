#pragma once

#define PY_SSIZE_T_CLEAN
#include <Python.h>

namespace gdee::python::api{

typedef struct {
    PyObject_HEAD // No semicolon after this, it's a macro!
    int number_for_testing_purposes;
    /* Type-specific fields go here. */
} UI_Object;

static void preRender(UI_Object* frame);
static void render(UI_Object* frame);
static void postRender(UI_Object* frame);

PyObject* PyInit_ui();

}