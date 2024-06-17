#include "image.h"

typedef struct _pyne_window_stub {
  PyObject_HEAD;

  SDL_Window *win_ptr;
  SDL_Renderer *render_ptr;
} _pyne_window_stub;

// Init/Delete
static i32 _pyne_image_init(_pyne_image *self, PyObject *args,
                            PyObject *kwargs) {
  char *path;
  char *kwords[] = {"path", NULL};

  if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s", kwords, &path)) {
    PyErr_SetString(_pyne_error, "couldn't parse the args");
    return -1;
  }

  const _pyne_window_stub *win = _pyne_default_window;
  if (win == NULL) {
    PyErr_SetString(_pyne_error, "no window initialized");
    return -1;
  }

  self->tex_ptr = IMG_LoadTexture(win->render_ptr, path);

  if (self->tex_ptr == NULL) {
    PyErr_SetString(_pyne_error, "cannot create an image");
    return -1;
  }

  return 0;
}

static void _pyne_image_del(_pyne_image *self) {
  SDL_DestroyTexture(self->tex_ptr);
  Py_TYPE(self)->tp_free(Py_TYPE(self));
}

// Methods
static PyObject *_pyne_image_get_size(_pyne_image *self, PyObject *args) {
  int w, h;
  SDL_QueryTexture(self->tex_ptr, NULL, NULL, &w, &h);

  return Py_BuildValue("ii", w, h);
}

// Method Define
static PyMethodDef _pyne_image_meth[] = {
    {"get_size", (PyCFunction)_pyne_image_get_size, METH_NOARGS,
     "get the size of an image"},
    {NULL, NULL, 0, NULL}};

// Type Define
PyTypeObject _pyne_image_type = {
    .ob_base = PyVarObject_HEAD_INIT(NULL, 0).tp_name = "_pyne.Image",
    .tp_doc = PyDoc_STR("Image class"),
    .tp_basicsize = sizeof(_pyne_image),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyType_GenericNew,
    .tp_methods = _pyne_image_meth,
    .tp_init = (initproc)_pyne_image_init,
    .tp_itemsize = 0,
    .tp_del = (destructor)_pyne_image_del};

i32 _pyne_prepare_image(PyObject *mod) {
  if (PyType_Ready(&_pyne_image_type))
    return -1;
  Py_INCREF(&_pyne_image_type);

  if (PyModule_AddObject(mod, "Image", (PyObject *)&_pyne_image_type) < 0) {
    Py_DECREF(&_pyne_image_type);
    return -1;
  }

  return 0;
}