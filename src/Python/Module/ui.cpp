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
typedef struct {
    PyObject_HEAD // No semicolon after this, it's a macro!
    int number_for_testing_purposes;
        /* Type-specific fields go here. */
} UI_Object;


// Deallocation method
static void UI_Dealloc(UI_Object* self) {
    // XDecRef any pyobjects being used in the struct
    Py_XDECREF(self->number_for_testing_purposes);
    Py_TYPE(self)->tp_free((PyObject*)self); // Free self
}

// New method
static PyObject* UI_New(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    UI_Object* self;
    self = (UI_Object*)type->tp_alloc(type, 0);

    if (self != NULL) {
        // Handle initalization of members here
        self->number_for_testing_purposes = 0;
    }

    return (PyObject*)self;
}

// Init method
static int Custom_init(UI_Object* self, PyObject* args, PyObject* kwds){
    static char* kwlist[] = {(char*)"number_for_testing_purposes", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|OOi", kwlist,
        &self->number_for_testing_purposes))
        return -1;
    return 0;
}

// define members
// NOTE: things get updated. Docs are out of date!
static PyMemberDef UI_members[] = {
    {"number", T_INT, offsetof(UI_Object, number_for_testing_purposes), 0, "custom number"}, 
    {NULL}  /* Sentinel */
};


// Define the type object, using the definitions above
static PyTypeObject UI_PType = {
    .ob_base = PyVarObject_HEAD_INIT(NULL, 0) // Manditory initializer
    .tp_name = "gdee.ui.UI", // The name of the type (TODO: manage later)
    .tp_basicsize = sizeof(UI_Object),
    .tp_itemsize = 0, // Size is so that python knows how much space to allocate. Itemsize is for variable-sized objects
    .tp_flags = Py_TPFLAGS_DEFAULT, // Manditory flags
    .tp_doc = PyDoc_STR("UI objects"), // Docstring
    .tp_new = PyType_GenericNew, // equivelant of __new__(), may change later
};

// Define module (this will be done in gdee.cpp)
static PyModuleDef UI_Module = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "gdee.ui",
    .m_doc = "Example module that creates an extension type.",
    .m_size = -1,
};
#pragma endregion

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

    Py_INCREF(&UI_PType);
    if (PyModule_AddObject(m, "UI", (PyObject*)&UI_PType) < 0) {
        Py_DECREF(&UI_PType);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}

