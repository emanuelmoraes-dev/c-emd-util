#ifndef _CEMDUTIL_ERROR_UTILITY_H_INCLUDED_
#define _CEMDUTIL_ERROR_UTILITY_H_INCLUDED_

#include <math.h>
#include "cemdutil/def.h"

#define EMD_MAX_ERR_STR_LEN 120

#define EMD_OK (0) // no errors
#define EMD_ERRNO (INT_MIN + 1) // the error is in errno
#define __EMD_ERRBASE (100) // all the erros of the CEMDUTIL library must to be between 100 (inclusive) and 200 (exclusive)

#define EMD_ERR_PANIC (__EMD_ERRBASE + 0)
#define EMD_ERR_PANIC_MESSAGE "unknown error"

#define EMD_ERR_OVERFLOW (__EMD_ERRBASE + 1)
#define EMD_ERR_OVERFLOW_MESSAGE "the value is greater than the maximum capacity of the number"

#define EMD_ERR_UNDERFLOW (__EMD_ERRBASE + 2)
#define EMD_ERR_UNDERFLOW_MESSAGE "the value is less than the minimum capacity of the number"

#define EMD_ERR_INDEX_OVERFLOW (__EMD_ERRBASE + 3)
#define EMD_ERR_INDEX_OVERFLOW_MESSAGE "the index is greater than the maximum capacity of list"

#define EMD_ERR_INVALID_TARGET (__EMD_ERRBASE + 4)
#define EMD_ERR_INVALID_TARGET_MESSAGE "the value is less than the minimum capacity of the list"

#define EMD_ERR_ERROR_NOT_PRESENT (__EMD_ERRBASE + 5)
#define EMD_ERR_ERROR_NOT_PRESENT_MESSAGE "the error is NULL"

#define EMD_ERR_INSTANCE_NOT_PRESENT (__EMD_ERRBASE + 6)
#define EMD_ERR_INSTANCE_NOT_PRESENT_MESSAGE "the struct instance is NULL"

#define EMD_ERR_ARG_NOT_PRESENT (__EMD_ERRBASE + 7)
#define EMD_ERR_ARG_NOT_PRESENT_MESSAGE "the function argument is NULL"

#define ERROR_DEF_STR(var) char var[EMD_MAX_ERR_STR_LEN]

#define ERROR_GET_MESSAGE(err) \
    (err) == EMD_ERR_PANIC ? EMD_ERR_PANIC_MESSAGE : (\
    (err) == EMD_ERR_OVERFLOW ? EMD_ERR_OVERFLOW_MESSAGE : (\
    (err) == EMD_ERR_UNDERFLOW ? EMD_ERR_UNDERFLOW_MESSAGE : (\
    (err) == EMD_ERR_INDEX_OVERFLOW ? EMD_ERR_INDEX_OVERFLOW_MESSAGE : (\
    (err) == EMD_ERR_INVALID_TARGET ? EMD_ERR_INVALID_TARGET_MESSAGE : (\
    (err) == EMD_ERR_ERROR_NOT_PRESENT ? EMD_ERR_ERROR_NOT_PRESENT_MESSAGE : (\
    (err) == EMD_ERR_INSTANCE_NOT_PRESENT ? EMD_ERR_INSTANCE_NOT_PRESENT_MESSAGE : (\
    (err) == EMD_ERR_ARG_NOT_PRESENT ? EMD_ERR_ARG_NOT_PRESENT_MESSAGE : "")))))))

#define ERROR_SET_ERR(err, value) \
    if ((err) != NULL) {\
        *(err) = (value);\
    }

#define ERROR_VERIFY_INSTANCE(err, instance, dr) \
    if ((instance) == NULL) {\
        ERROR_SET_ERR(err, EMD_ERR_INSTANCE_NOT_PRESENT)\
        return dr;\
    }

#define ERROR_VERIFY_ARG(err, arg, dr) \
    if ((arg) == NULL) {\\
        ERROR_SET_ERR(err, EMD_ERR_ARG_NOT_PRESENT)\
        return dr;\
    }

#define ERROR_IS_OVERFLOW_ADD(a, x, MIN_VALUE, MAX_VALUE) \
    (((x) > 0) && ((a) > (MAX_VALUE) - (x)))

#define ERROR_IS_UNDERFLOW_ADD(a, x, MIN_VALUE, MAX_VALUE) \
    (((x) < 0) && ((a) < (MIN_VALUE) - (x)))

#define ERROR_CHECK_OVERFLOW_ADD(a, x, MIN_VALUE, MAX_VALUE) (\
    ERROR_IS_OVERFLOW_ADD(a, x, MIN_VALUE, MAX_VALUE) ? EMD_ERR_OVERFLOW :\
    ERROR_IS_UNDERFLOW_ADD(a, x, MIN_VALUE, MAX_VALUE) ? EMD_ERR_UNDERFLOW :\
    EMD_OK\
)

#define ERROR_IS_OVERFLOW_SUB(a, x, MIN_VALUE, MAX_VALUE) \
    (((x) < 0) && ((a) > (MAX_VALUE) + (x)))

#define ERROR_IS_UNDERFLOW_SUB(a, x, MIN_VALUE, MAX_VALUE) \
    (((x) > 0) && ((a) < (MIN_VALUE) + (x)))

#define ERROR_CHECK_OVERFLOW_SUB(a, x, MIN_VALUE, MAX_VALUE) (\
    ERROR_IS_OVERFLOW_SUB(a, x, MIN_VALUE, MAX_VALUE) ? EMD_ERR_OVERFLOW :\
    ERROR_IS_UNDERFLOW_SUB(a, x, MIN_VALUE, MAX_VALUE) ? EMD_ERR_UNDERFLOW :\
    EMD_OK\
)

#define __ERROR_IS_OVERFLOW_ABS_MULT(a, x, MIN_VALUE, MAX_VALUE) \
    ((x) && (a) > (MAX_VALUE) / (x))

#define __ERROR_IS_UNDERFLOW_MULT(a_negative, x_positive, MIN_VALUE, MAX_VALUE) \
    ((x_positive) && (a_negative) < (MIN_VALUE) / (x_positive))

#define __ERROR_ABS(a) \
    ((a) < 0 ? (a) * (-1) : (a))

#define __ERROR_MULT_IS_NEGATIVE(a, x) (\
    ((a) < 0 && (x) > 0) ||\
    ((a) > 0 && (x) < 0)\
)

#define __ERROR_MULT_GET_NEGATIVE(a, x) \
    ((a) < 0 ? (a) : (x))

#define __ERROR_MULT_GET_POSITIVE(a, x) \
    ((a) > 0 ? (a) : (x))

#define ERROR_IS_OVERFLOW_MULT(a, x, MIN_VALUE, MAX_VALUE) (\
    (((a) == -1) && ((x) == (MIN_VALUE))) ||\
    (((x) == -1) && ((a) == (MIN_VALUE))) ||\
    (\
        (!__ERROR_MULT_IS_NEGATIVE(a, x)) &&\
        __ERROR_IS_OVERFLOW_ABS_MULT(\
            __ERROR_ABS(a),\
            __ERROR_ABS(x),\
            MIN_VALUE,\
            MAX_VALUE\
        )\
    )\
)

#define ERROR_IS_UNDERFLOW_MULT(a, x, MIN_VALUE, MAX_VALUE) (\
    __ERROR_MULT_IS_NEGATIVE(a, x) &&\
    __ERROR_IS_UNDERFLOW_MULT(\
        __ERROR_MULT_GET_NEGATIVE(a, x),\
        __ERROR_MULT_GET_POSITIVE(a, x),\
        MIN_VALUE,\
        MAX_VALUE\
    )\
)

#define ERROR_CHECK_OVERFLOW_MULT(a, x, MIN_VALUE, MAX_VALUE) (\
    ERROR_IS_OVERFLOW_MULT(a, x, MIN_VALUE, MAX_VALUE) ? EMD_ERR_OVERFLOW :\
    ERROR_IS_UNDERFLOW_MULT(a, x, MIN_VALUE, MAX_VALUE) ? EMD_ERR_UNDERFLOW :\
    EMD_OK\
)

#endif
