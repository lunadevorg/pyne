#include "window.h"
#include "SDL_render.h"
#include "SDL_video.h"
#include <stdio.h>

// Methods
static i32 _pyne_window_init(_pyne_window *win, PyObject *args,
                             PyObject *kwargs) {
  char *kwords[] = {"title", "width", "height", "flags", NULL};

  char *title;
  i32 width, height;
  u32 flags = 0;

  if (!PyArg_ParseTupleAndKeywords(args, kwargs, "sii|I", kwords, &title,
                                   &width, &height, &flags)) {
    PyErr_SetString(_pyne_error, "couldn't parse the args");
    return -1;
  }

  win->win_ptr = SDL_CreateWindow((const char *)title, SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, width, height, flags);
  win->render_ptr =
      SDL_CreateRenderer(win->win_ptr, -1, SDL_RENDERER_ACCELERATED);

  if (win->win_ptr == NULL || win->render_ptr == NULL) {
    PyErr_SetString(_pyne_error, "cannot create the window object");
    return -1;
  }

  return 0;
}

static void _pyne_window_del(_pyne_window *self) {
  SDL_DestroyRenderer(self->render_ptr);
  SDL_DestroyWindow(self->win_ptr);
  Py_TYPE(self)->tp_free(Py_TYPE(self));
}

// Method Define
static PyMethodDef _pyne_window_meth[] = {{NULL, NULL, 0, NULL}};

// Type Define
PyTypeObject _pyne_window_type = {
    .ob_base = PyVarObject_HEAD_INIT(NULL, 0).tp_name = "_pyne.Window",
    .tp_doc = PyDoc_STR("Main window class, only create one per program"),
    .tp_basicsize = sizeof(_pyne_window),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyType_GenericNew,
    .tp_methods = _pyne_window_meth,
    .tp_init = (initproc)_pyne_window_init,
    .tp_itemsize = 0,
    .tp_del = (destructor)_pyne_window_del};

i32 _pyne_prepare_window(PyObject *mod) {
  if (PyType_Ready(&_pyne_window_type))
    return -1;
  Py_INCREF(&_pyne_window_type);

  if (PyModule_AddObject(mod, "Window", (PyObject *)&_pyne_window_type) < 0) {
    Py_DECREF(&_pyne_window_type);
    return -1;
  }

  return 0;
}