#include "_pyne.h"
#include "window.h"

PyObject *_pyne_error = NULL;

static PyMethodDef _pyne_methods[] = {NULL};

static PyModuleDef _pyne_module = {PyModuleDef_HEAD_INIT, "pyne", NULL, -1,
                                   .m_methods = _pyne_methods};

PyMODINIT_FUNC PyInit__pyne(void) {
  PyObject *m = PyModule_Create(&_pyne_module);

  if (_pyne_prepare_window(m) == -1) {
    Py_DECREF(m);
    return NULL;
  }

  _pyne_error = PyErr_NewException("_pyne._error", NULL, NULL);

  return m;
}
