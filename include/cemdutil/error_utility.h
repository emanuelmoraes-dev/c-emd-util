#ifndef C_EMD_UTIL_ERROR_UTILITY_H_INCLUDED
#define ifndef C_EMD_UTIL_ERROR_UTILITY_H_INCLUDED

#include "cemdutil/types.h"

#define ERROR_MAX(x, y) (((x) > (y)) ? (x) : (y))
#define ERROR_MIN(x, y) (((x) < (y)) ? (x) : (y))
#define ERROR_MOD(v) (v) < 0 ? (-v) : (v)
#define ERROR_VERIFY_OVERFLOW_ADD(v1, v2, t) if((v1) != ((t)((v1) + (v2))) - (v2)) return EMD_OVERFLOW
#define ERROR_VERIFY_OVERFLOW_PLUS(v1, v2, t) if(ERROR_MAX(ERROR_MOD(v1), ERROR_MOD(v2)) != ((t)((v1) * (v2))) / ((long double)ERROR_MIN(ERROR_MOD(v1), ERROR_MOD(v2)))) return EMD_OVERFLOW
#define ERROR_VERIFY_OVERFLOW_DIV(v1, v2, t) if((v1) != ((t)((v1) / (v2))) * (v2)) return EMD_OVERFLOW

#endif // ifndef C_EMD_UTIL_ERROR_UTILITY_H_INCLUDED
