#include "window.h"
#include <stdio.h>

// Init/Delete
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

// Methods
static PyObject *_pyne_window_update(_pyne_window *self, PyObject *_args,
                                     PyObject *_kwargs) {
  SDL_RenderPresent(self->render_ptr);
  Py_RETURN_NONE;
}

static PyObject *_pyne_window_fill(_pyne_window *self, PyObject *args,
                                   PyObject *kwargs) {
  u8 r, g, b, a = 255;

  if (!PyArg_ParseTuple(args, "BBB|B", &r, &g, &b, &a)) {
    PyErr_SetString(_pyne_error, "couldn't parse args");
    return NULL;
  }

  SDL_SetRenderDrawColor(self->render_ptr, r, g, b, a);
  SDL_RenderClear(self->render_ptr);
  Py_RETURN_NONE;
}

// Get/Setters
static PyObject *_pyne_window_getsize(_pyne_window *self, void *_closure) {
  i32 x, y;
  SDL_GetWindowSize(self->win_ptr, &x, &y);
  return Py_BuildValue("ii", x, y);
}

static i32 _pyne_window_setsize(_pyne_window *self, PyObject *args,
                                void *_closure) {
  i32 x, y;

  if (!PyArg_ParseTuple(args, "ii", &x, &y)) {
    return -1;
  }

  SDL_SetWindowSize(self->win_ptr, x, y);
  return 0;
}

static PyObject *_pyne_window_gettitle(_pyne_window *self, void *_closure) {
  return PyUnicode_FromString(SDL_GetWindowTitle(self->win_ptr));
}

static i32 _pyne_window_settitle(_pyne_window *self, PyObject *value,
                                 void *_closure) {
  char *new_title;
  if (!PyArg_Parse(value, "s", &new_title)) {
    return -1;
  }
  SDL_SetWindowTitle(self->win_ptr, new_title);

  return 0;
}

// Method Define
static PyMethodDef _pyne_window_meth[] = {
    {"update", (PyCFunction)_pyne_window_update, METH_NOARGS,
     "update the window's pixels"},
    {"fill", (PyCFunction)_pyne_window_fill, METH_VARARGS,
     "fill the screen with color"},
    {NULL, NULL, 0, NULL}};
static PyGetSetDef _pyne_window_getset[] = {
    {"size", (getter)_pyne_window_getsize, (setter)_pyne_window_setsize,
     "size of the window", NULL},
    {"title", (getter)_pyne_window_gettitle, (setter)_pyne_window_settitle,
     "title of the window", NULL},
    {NULL, NULL, NULL, NULL, NULL}};

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
    .tp_del = (destructor)_pyne_window_del,
    .tp_getset = _pyne_window_getset};

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
