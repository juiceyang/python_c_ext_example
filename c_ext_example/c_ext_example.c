#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <string.h>

static PyObject*
foo(PyObject* self, PyObject *args) {
	return PyUnicode_FromString("return from foo");
}

static PyObject*
bar(PyObject* self, PyObject *args) {
    const char* input;
    if (!PyArg_ParseTuple(args, "s", &input) < 0) {
        return NULL;
    }
    const int len = strlen(input);
    const char* prefix = "return from bar: ";
    char* output[1024];
    sprintf(output, "%s%s", prefix, input);
	return PyUnicode_FromString(output);
}

static PyMethodDef CExtExampleMethods[] = {
    {"foo", foo, METH_VARARGS, "foo doc"},
    {"bar", bar, METH_VARARGS, "bar doc"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef CExtExampleModule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "c_ext_example",
    .m_doc = "c_ext_example doc",
    .m_size = -1,
    .m_methods = CExtExampleMethods
};

PyMODINIT_FUNC
PyInit_c_ext_example() {
	PyObject* m;
    m = PyModule_Create(&CExtExampleModule);
    return m;
}

