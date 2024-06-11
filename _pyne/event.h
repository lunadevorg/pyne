#ifndef __EVENT_H__
#define __EVENT_H__

#include "_pyne.h"

void _pyne_prepare_events();

PyObject *_pyne_attach_handler(PyObject *args, PyObject *kwargs);
PyObject *_pyne_update(PyObject *args, PyObject *kwargs);
PyObject *_pyne_get_handlers(PyObject *, PyObject *args);

#endif
