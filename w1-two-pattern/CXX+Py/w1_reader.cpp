#include <Python.h>
#include <iostream>
#include <ctime>

int main(int argc, char **argv)
{
    PyObject *pName, *pModule, *pFunc, *pFunc2;
    PyObject *pArgs, *pValue, *pValue2;
	Py_ssize_t psize;
	
    int i = 0;
	const std::string MY_MODULE = "device";
	const std::string MY_FUNC1 = "ready";
	const std::string MY_FUNC2 = "w1";
	char *w1_dir = nullptr, *ret = nullptr;
	
    Py_Initialize();
    /** Python2.7 PYTHONPATH 未設定時のカレントディレクトリ捕捉 */
    //PyObject *sys = PyImport_ImportModule("sys");
    //PyObject *path = PyObject_GetAttrString(sys, "path");
    //PyList_Append(path, PyString_FromString("."));
    //PySys_SetArgv(argc, argv);
    /***************************************************************/
    //PyObject* sysPath = PySys_GetObject("path");
	//PyObject* dirPath = PyString_FromString(".");
	//PyList_Append(sysPath, dirPath);
	//pName = PyString_FromString(MY_MODULE.c_str()); 
	/***************************************************************/
	/*** Python3.3 over PyUnicode_AsUTF8のせいで */
	//PyObject* sysPath = PySys_GetObject("path");
	//PyObject* dirPath = PyUnicode_DecodeFSDefault(".");
	//PyList_Append(sysPath, dirPath);
	//pName = PyUnicode_DecodeFSDefault(MY_MODULE.c_str()); 
	/****************************************************************/
	/*** PYTHONPATH ***********************************/
	PyObject* sys = PyImport_ImportModule("sys");
	PyObject* sysPath = PyObject_GetAttrString(sys, "path");
	PyObject* dirPath = PyUnicode_DecodeFSDefault("$HOME/MyDaq/w1-two-pattern/CXX+Py");
	PyList_Append(sysPath, dirPath); 
	/****************************************************************/
    
    pName = PyUnicode_DecodeFSDefault(MY_MODULE.c_str());
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);
    if (pModule != nullptr) {
        // Func1
        pFunc = PyObject_GetAttrString(pModule, MY_FUNC1.c_str());
        if (pFunc && PyCallable_Check(pFunc)) {
            pValue = PyObject_CallObject(pFunc, nullptr);
            if (pValue != nullptr) {
                //w1_dir = PyString_AsString(pValue); // Python2.7
                w1_dir = PyUnicode_AsUTF8AndSize(pValue, &psize);
                Py_DECREF(pValue);
            }
            else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr,"Call failed\n");
                return 1;
            }
        }
        else {
            if (PyErr_Occurred())
				PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", MY_FUNC1.c_str());
        }
		
		std::cout << w1_dir << std::endl;
		
		// Func2
		pFunc2 = PyObject_GetAttrString(pModule, MY_FUNC2.c_str());    
		if (pFunc2 && PyCallable_Check(pFunc2)) {
			pArgs = PyTuple_New(1);
			/** python2 */
			//PyTuple_SetItem(pArgs, 0, PyString_FromString(w1_dir)); 
			/*** python3 */
			pValue2 = PyUnicode_FromString(w1_dir);
			if (!pValue2) {
                Py_DECREF(pArgs);
                Py_DECREF(pModule);
				fprintf(stderr, "Cannot convert argument\n");
				return 1;
			}
			PyTuple_SetItem(pArgs, 0, pValue2); 
			
			while (i < 10) {
				pValue2 = PyObject_CallObject(pFunc2, pArgs);
				if (pValue2 != nullptr) {
					/** python2 */
					//ret = PyString_AsString(pValue2);
					
					/*** python3 */
    				ret = PyUnicode_AsUTF8AndSize(pValue2, &psize);
    				
					Py_DECREF(pValue2);
				}
				else {
					Py_DECREF(pFunc2);
					Py_DECREF(pModule);
					PyErr_Print();
					fprintf(stderr,"Call failed\n");
					return 1;
				}
				std::cout << ret << std::endl;
				i++;
				sleep(1);
			}
			Py_DECREF(pArgs);
		}
		else {
            if (PyErr_Occurred())
				PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", MY_FUNC2.c_str());
        }
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", MY_MODULE.c_str());
        return 1;
    }
    Py_DECREF(pFunc);
    Py_XDECREF(pFunc2);
    Py_DECREF(pModule);
    Py_Finalize();
    return 0;
}
