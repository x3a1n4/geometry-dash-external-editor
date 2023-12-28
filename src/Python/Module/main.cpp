static int numargs = 0;

#include <python3.11/Python.h>

class GdeeModule {
// Implement python module
// from https://docs.python.org/3/extending/embedding.html
public:
    static PyObject* PyInit_GDEE(void) {
        return PyModule_Create(&EmbModule);
    }

private:
    // Define the moule
    static PyModuleDef GdeeModule = {
    PyModuleDef_HEAD_INIT, "gdee", NULL, -1, GdeeMethods,
    NULL, NULL, NULL, NULL
    };

    // Define methods available here!
    // TODO: a ton. This will needd to be separated quite a bit, since we'll probably provide hundreds of methods here
    static PyMethodDef GdeeMethods[] = {
    {"test", test_function, METH_VARARGS,
     "Return the number of arguments received by the process."},
    {NULL, NULL, 0, NULL}
    };

    // Define a test function
    // This will be expanded later
    static PyObject* test_function(PyObject* self, PyObject* args)
    {
        return PyUnicode_FromString("Hello World!");
    }
};