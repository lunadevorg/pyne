#ifndef ___PYNE_H__
#define ___PYNE_H__

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <SDL2/SDL.h>
#include <stdint.h>

/*
 *	Defines for the library.
 */

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef void *opaq;

extern PyObject *_pyne_error;
extern PyObject *_pyne_default_window;

#endif
