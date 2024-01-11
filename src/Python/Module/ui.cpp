// Class that defines UI
// Addons will implement classes that extend this class
#define PY_SSIZE_T_CLEAN

#include "ui.h"
#include "gdee.h"
#include <string>

#include <stddef.h> /* for offsetof() */
#include <python3.11/Python.h>
#include <python3.11/structmember.h> // https://stackoverflow.com/questions/12044036/cpython-api-jiving-with-c-class

// Define UI class

// From https://docs.python.org/3/extending/newtypes_tutorial.html
// This is what the custom object actually contains (aka the data)
// It is allocated for each custom object instance in python

#pragma region UI Class
// As for a python UI object, it only really contains the methods for rendering. It doesn't have any inherent data.

// Deallocation method
static void UI_Dealloc(UIModule::UI_Object* self) {
    // XDecRef any pyobjects being used in the struct
    Py_XDECREF(self->number_for_testing_purposes);
    Py_TYPE(self)->tp_free((PyObject*)self); // Free self
}

// New method
static PyObject* UI_New(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    UIModule::UI_Object* self;
    self = (UIModule::UI_Object*)type->tp_alloc(type, 0);

    if (self != NULL) {
        // Handle initalization of members here
        self->number_for_testing_purposes = 0;
    }

    return (PyObject*)self;
}

// Init method
static int UI_Init(UIModule::UI_Object* self, PyObject* args, PyObject* kwds){
    static char* kwlist[] = {(char*)"number_for_testing_purposes", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|OOi", kwlist,
        &self->number_for_testing_purposes))
        return -1;
    return 0;
}

// define members
// NOTE: things get updated. Docs are out of date!
static PyMemberDef UI_members[] = {
    {"number", T_INT, offsetof(UIModule::UI_Object, number_for_testing_purposes), 0, "custom number"},
    {NULL}  /* Sentinel */
};

// define methods
// these methods should ultimately get defined in the python code itself
static PyObject* UI_preRender(UIModule::UI_Object* self, PyObject* Py_UNUSED(ignored)) {

}

static PyObject* UI_render(UIModule::UI_Object* self, PyObject* Py_UNUSED(ignored)) {

}

static PyObject* UI_postRender(UIModule::UI_Object* self, PyObject* Py_UNUSED(ignored)) {

}

void UIModule::preRender(UIModule::UI_Object* frame) {
    UI_preRender(frame, nullptr);
};
void UIModule::render(UIModule::UI_Object* frame) {
    UI_render(frame, nullptr);
};
void UIModule::postRender(UIModule::UI_Object* frame) {
    UI_postRender(frame, nullptr);
};

// Get methods
static PyMethodDef UI_methods[] = {
    {"preRender", (PyCFunction)UI_preRender, METH_NOARGS,
     "Perform any operations before rendering"
    },
    {"render", (PyCFunction)UI_render, METH_NOARGS, // Note: may need args here
     "Render elements to the screen"
    },
    {"postRender", (PyCFunction)UI_postRender, METH_NOARGS,
     "Perform any operations after rendering"
    },
    {NULL}  /* Sentinel */
};


// Define the type object, using the definitions above
static PyTypeObject UI_PType = {
    .ob_base = PyVarObject_HEAD_INIT(NULL, 0) // Manditory initializer
    .tp_name = "gdee.ui.UI", // The name of the type (TODO: manage later)
    .tp_basicsize = sizeof(UIModule::UI_Object),
    .tp_itemsize = 0, // Size is so that python knows how much space to allocate. Itemsize is for variable-sized objects
    .tp_dealloc = (destructor)UI_Dealloc,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, // Default flag is manditory, basetype flag means ???
    .tp_doc = PyDoc_STR("UI objects"), // Docstring
    .tp_methods = UI_methods,
    .tp_members = UI_members,
    .tp_init = (initproc)UI_Init,
    .tp_new = PyType_GenericNew, // equivelant of __new__(), may change later
};
#pragma endregion

#pragma region UI Functions
static PyObject* registerUIElement(PyObject* self, PyObject* args) {
    // TODO: manage this
}

static PyObject* unregisterUIElement(PyObject* self, PyObject* args) {
    // TODO: manage this
}

static PyMethodDef methods[] = {
    {"register", registerUIElement, METH_VARARGS,
     "Register a Dear Imgui frame with the UI manager"},
    {"unregister", registerUIElement, METH_VARARGS,
     "Unregister a Dear Imgui frame with the UI manager"},
    {NULL, NULL, 0, NULL}
};
#pragma endregion


// Define module (this will be done in gdee.cpp)
static PyModuleDef UI_Module = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "gdee.ui",
    .m_doc = "Example module that creates an extension type.",
    .m_size = -1,
    .m_methods = methods
};

PyMODINIT_FUNC
PyInit_custom(void)
{
    // Initialize the custom type
    PyObject* m;
    if (PyType_Ready(&UI_PType) < 0)
        return NULL;

    // Initialize the module
    m = PyModule_Create(&UI_Module);
    if (m == NULL)
        return NULL;

    // Add UI type
    Py_INCREF(&UI_PType);
    if (PyModule_AddObject(m, "UI", (PyObject*)&UI_PType) < 0) {
        Py_DECREF(&UI_PType);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}

