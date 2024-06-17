#include "event.h"
#include "window.h"

PyObject *_pyne_error = NULL;
PyObject *_pyne_default_window = NULL;

static PyMethodDef _pyne_methods[] = {
    {"update", _pyne_update, METH_NOARGS, "update the module's data"},
    {"attach_handler", _pyne_attach_handler, METH_VARARGS,
     "attach handler to an event"},
    {"_get_handlers", _pyne_get_handlers, METH_NOARGS,
     "use to check if handler was registered"},
    {NULL}};

static PyModuleDef _pyne_module = {PyModuleDef_HEAD_INIT, "pyne", NULL, -1,
                                   .m_methods = _pyne_methods};

PyMODINIT_FUNC PyInit__pyne(void) {
  SDL_Init(SDL_INIT_EVERYTHING);
  IMG_Init(IMG_INIT_JPG || IMG_INIT_PNG || IMG_INIT_WEBP);

  _pyne_default_window = NULL;
  PyObject *m = PyModule_Create(&_pyne_module);

  if (_pyne_prepare_window(m) == -1 || _pyne_prepare_image(m) == -1) {
    Py_DECREF(m);
    return NULL;
  }

  _pyne_error = PyErr_NewException("_pyne._error", NULL, NULL);
  _pyne_prepare_events();

  return m;
}
