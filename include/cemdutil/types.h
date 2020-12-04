#ifndef C_EMD_UTIL_TYPES_H_INCLUDED
#define C_EMD_UTIL_TYPES_H_INCLUDED

#include <limits.h>

#define EMD_OK 0
#define EMD_ERRNO (INT_MIN + 1)
#define EMD_OVERFLOW 1001
#define EMD_INDEX_OVERFLOW 1002

typedef int EMD_ERR;
typedef char EMD_BIT;

#endif // C_EMD_UTIL_TYPES_H_INCLUDED
