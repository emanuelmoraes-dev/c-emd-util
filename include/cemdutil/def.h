#ifndef _CEMDUTIL_DEF_H_INCLUDED_
#define _CEMDUTIL_DEF_H_INCLUDED_

#include <limits.h>

#define EMD_OK (0) // no errors
#define EMD_ERRNO (INT_MIN + 1) // the error is in errno
#define __EMD_ERRBASE (100) // all the erros of the CEMDUTIL library must to be between 100 (inclusive) and 200 (exclusive)
#define EMD_ERR_PANIC (__EMD_ERRBASE + 0) // unknown error
#define EMD_ERR_OVERFLOW (__EMD_ERRBASE + 1) // the value is greater than the maximum capacity of the number
#define EMD_ERR_UNDERFLOW (__EMD_ERRBASE + 2) // the value is less than the minimum capacity of the number
#define EMD_ERR_INDEX_OVERFLOW (__EMD_ERRBASE + 3) // the index is greater than the maximum capacity of list
#define EMD_ERR_INVALID_TARGET (__EMD_ERRBASE + 4) // the value is less than the minimum capacity of the list
#define EMD_ERR_ERROR_NOT_PRESENT (__EMD_ERRBASE + 5) // the error is NULL
#define EMD_ERR_INSTANCE_NOT_PRESENT (__EMD_ERRBASE + 6) // the struct instance is NULL
#define EMD_ERR_ARG_NOT_PRESENT (__EMD_ERRBASE + 7) // the function argument is NULL

typedef unsigned int EMD_ERR; // error type
typedef char EMD_BIT; // bit type
typedef unsigned int EMD_SIZE; // list size type
#define EMD_SIZE_MIN (0) // the min value of EMD_SIZE
#define EMD_SIZE_MAX (UINT_MAX) // the max value of EMD_SIZE

#endif
