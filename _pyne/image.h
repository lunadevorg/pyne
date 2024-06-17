#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "_pyne.h"
#include <SDL2/SDL_image.h>

typedef struct _pyne_image {
  PyObject_HEAD;
  SDL_Texture *tex_ptr;
} _pyne_image;

extern PyTypeObject _pyne_image_type;
i32 _pyne_prepare_image(PyObject *);

#endif