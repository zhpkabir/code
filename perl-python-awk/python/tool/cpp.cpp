/* 
 * test.cpp 
 *  Created on: 2010-8-12 
 *      Author: lihaibo 
 */  
#include <Python.h>  
#include <iostream>  
#include <string>  
void printDict(PyObject* obj) {  
	if (!PyDict_Check(obj))  
		return;  
	PyObject *k, *keys;  
	keys = PyDict_Keys(obj);  
	for (int i = 0; i < PyList_GET_SIZE(keys); i++) {  
		k = PyList_GET_ITEM(keys, i);  
		char* c_name = PyString_AsString(k);  
		printf("%s\n", c_name);  
	}  
}  
int main() {  
	Py_Initialize();  
	if (!Py_IsInitialized())  
		return -1;  
	PyRun_SimpleString("import sys");  
	PyRun_SimpleString("sys.path.append('./')");  

	PyObject* pModule = PyImport_ImportModule("testpy");  
	if (!pModule) {  
		printf("Cant open python file!\n");  
		return -1;  
	}  

	PyObject* pDict = PyModule_GetDict(pModule);  
	if (!pDict) {  
		printf("Cant find dictionary.\n");  
		return -1;  
	}  
	
	printDict(pDict);  
	PyObject* pFunHi = PyDict_GetItemString(pDict, "sayhi");  
	PyObject_CallFunction(pFunHi, "s", "lhb");  
	Py_DECREF(pFunHi);  
	PyObject* pClassSecond = PyDict_GetItemString(pDict, "Second");  
	if (!pClassSecond) {  
		printf("Cant find second class.\n");  
		return -1;  
	}  

	PyObject* pClassPerson = PyDict_GetItemString(pDict, "Person");  
	if (!pClassPerson) {  
		printf("Cant find person class.\n");  
		return -1;  
	}  

	PyObject* pInstanceSecond = PyInstance_New(pClassSecond, NULL, NULL);  
	if (!pInstanceSecond) {  
		printf("Cant create second instance.\n");  
		return -1;  
	}  
	
	PyObject* pInstancePerson = PyInstance_New(pClassPerson, NULL, NULL);  
	if (!pInstancePerson) {  
		printf("Cant find person instance.\n");  
		return -1;  
	}  
	PyObject_CallMethod(pInstanceSecond, "invoke", "O", pInstancePerson);  
	
	Py_DECREF(pInstanceSecond);  
	Py_DECREF(pInstancePerson);  
	Py_DECREF(pClassSecond);  
	Py_DECREF(pClassPerson);  
	Py_DECREF(pModule);  
	Py_Finalize();  
	return 0;  
}  
