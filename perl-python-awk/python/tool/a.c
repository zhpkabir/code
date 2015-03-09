#include <Python.h> 

int  main(int  argc, char * argv[])
{
	Py_Initialize();

	PyRun_SimpleString("x = 10" );
	PyRun_SimpleString("y = 20" );
	PyObject* mainModule = PyImport_ImportModule("__main__" );
	PyObject* dict = PyModule_GetDict(mainModule);
	PyObject* resultObject = PyRun_String("x + y" , Py_eval_input, dict, dict);

	if (resultObject)
	{
		int result = PyLong_AsLong(resultObject);
		printf("%d \n" , result);
		Py_DECREF(resultObject);
	}

	Py_Finalize();
	return  0 ;
}
