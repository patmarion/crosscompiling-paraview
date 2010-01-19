#include "Python.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
  // Initialize python
  Py_SetProgramName(argv[0]);
  Py_Initialize();

  // Run a piece of python code
  const char* code = "msg = 'hello world'\n";
  PyRun_SimpleString((char*)code);

  // Get the dictionary for the __main__ module
  PyObject* main_module = PyImport_AddModule((char*)"__main__");
  PyObject* global_dict = PyModule_GetDict(main_module);

  // Lookup the 'msg' object, convert to string, and print it
  PyObject* string_object = PyDict_GetItemString(global_dict, "msg");
  char* string_ptr = PyString_AsString(string_object);
  printf("%s\n", string_ptr);

  // Finalize python
  Py_Finalize();
}

