#include "event.h"

static PyObject *handlers;

void _pyne_prepare_events() { handlers = PyDict_New(); }

PyObject *_pyne_attach_handler(PyObject *self, PyObject *args) {
  i32 event_id = 0;
  PyObject *func;

  if (!PyArg_ParseTuple(args, "iO", &event_id, &func)) {
    return NULL;
  }

  if (!PyCallable_Check(func)) {
    PyErr_SetString(_pyne_error, "func is not callable");
    return NULL;
  }

  Py_XINCREF(func);
  PyDict_SetItem(handlers, PyLong_FromLong(event_id), func);

  Py_RETURN_NONE;
}

PyObject *_pyne_update(PyObject *args, PyObject *kwargs) {
  SDL_Event ev;

  while (SDL_PollEvent(&ev)) {
    PyObject *func = PyDict_GetItem(handlers, PyLong_FromLong(ev.type));
    if (func) {
      PyObject_CallNoArgs(func);
    }
  }

  Py_RETURN_NONE;
}

PyObject *_pyne_get_handlers(PyObject *args_, PyObject *args) {
  return handlers;
}
