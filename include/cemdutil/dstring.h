#ifndef _CEMDUTIL_DSTRING_H_INCLUDED_
#define _CEMDUTIL_DSTRING_H_INCLUDED_

#include <stdlib.h>
#include "cemdutil/def.h"

#define STRING_DEFAULT_MIN_EXTRA 20 // Minimum amount of extra space in memory reallocation
#define STRING_DEFAULT_REALLOCATE_STRATEGY STRING_HALF_REALLOCATE_STRATEGY // Standard memory reallocation strategy

/**
 * Defines the memory allocation strategy that the String will have
 *
 * @param length_allocated Currently allocated space
 * @param size Current DString size
 * @param err Reference to store the value of the error if it occurs. If not assigned,
 *            the value is automatically set to 0 (no errors). It cannot be null
 * @return new space to be reallocated (if not enough, the function will be called again)
 */
typedef size_t StringReallocateStrategy(size_t length_allocated, size_t lenght, EMD_ERR* err);

#endif
