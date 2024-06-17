#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "_pyne.h"
#include "image.h"

typedef struct _pyne_window {
  PyObject_HEAD;

  SDL_Window *win_ptr;
  SDL_Renderer *render_ptr;
} _pyne_window;

extern PyTypeObject _pyne_window_type;

i32 _pyne_prepare_window(PyObject *);

#endif
