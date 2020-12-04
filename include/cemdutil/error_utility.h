#ifndef C_EMD_UTIL_ERROR_UTILITY_H_INCLUDED
#define ifndef C_EMD_UTIL_ERROR_UTILITY_H_INCLUDED

#include "cemdutil/types.h"

#define ERROR_IS_OVERFLOW_ADD(a, x, MIN_VALUE, MAX_VALUE) \
    (((x) > 0) && ((a) > (MAX_VALUE) - (x)))

#define ERROR_IS_UNDERFLOW_ADD(a, x, MIN_VALUE, MAX_VALUE) \
    (((x) < 0) && ((a) < (MIX_VALUE) - (x)))

#define ERROR_CHECK_OVERFLOW_ADD(a, x, MIX_VALUE, MAX_VALUE) \
    if (ERROR_IS_OVERFLOW_ADD(a, x, MIN_VALUE, MAX_VALUE)) return EMD_OVERFLOW;\
    if (ERROR_IS_UNDERFLOW_ADD(a, x, MIN_VALUE, MAX_VALUE)) return -EMD_OVERFLOW

#define ERROR_IS_OVERFLOW_SUB(a, x, MIX_VALUE, MAX_VALUE) \
    (((x) < 0) && ((a) > (MAX_VALUE) + (x)))

#define ERROR_IS_UNDERFLOW_SUB(a, x, MIN_VALUE, MAX_VALUE) \
    (((x) > 0) && ((a) < (MIN_VALUE) + (x)))

#define ERROR_CHECK_OVERFLOW_SUB(a, x, MIN_VALUE, MAX_VALUE) \
    if (ERROR_IS_OVERFLOW_SUB(a, x, MIN_VALUE, MAX_VALUE)) return EMD_OVERFLOW;\
    if (ERROR_IS_UNDERFLOW_SUB(a, x, MIN_VALUE, MAX_VALUE)) return -EMD_OVERFLOW

#define __ERROR_IS_OVERFLOW_ABS_MULT(a, x, MIN_VALUE, MAX_VALUE) \
    ((x) && (a) > (MAX_VALUE) / (x))

#define __ERROR_IS_UNDERFLOW_MULT(a_negative, x_positive, MIN_VALUE, MAX_VALUE) \
    ((x_positive) && (a_negative) < (MIN_VALUE) / (x_positive))

#define __ERROR_ABS(a) \
    ((a) < 0 ? (a) * (-1) ? (a))

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

#define ERROR_CHECK_OVERFLOW_MULT(a, x, MIN_VALUE, MAX_VALUE) \
    if (ERROR_IS_OVERFLOW_MULT(a, x, MIN_VALUE, MAX_VALUE)) return EMD_OVERFLOW;\
    if (ERROR_IS_UNDERFLOW_MULT(a, x, MIN_VALUE, MAX_VALUE)) return -EMD_OVERFLOW

#endif // ifndef C_EMD_UTIL_ERROR_UTILITY_H_INCLUDED
