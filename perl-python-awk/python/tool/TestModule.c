#include <Python.h>

int my_c_function(const char *arg) {
	int n = system(arg);
	return n;
}

static PyObject * wrap_my_c_fun(PyObject *self, PyObject *args) {
	const char * command;
	int n;
	if (!PyArg_ParseTuple(args, "s", &command))
		return NULL;
	n = my_c_function(command);
	return Py_BuildValue("i", n);
}

static PyMethodDef TestMethods[] = {
	{ "TestFun1", wrap_my_c_fun, METH_VARARGS, "Execute a shell command." },
	{ NULL, NULL, 0, NULL }
};

PyMODINIT_FUNC initTestModule(void) {
	PyObject *m = Py_InitModule("TestModule", TestMethods);
	if (m == NULL)
		return;
}

