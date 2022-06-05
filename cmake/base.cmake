add_library(
    base
    INTERFACE
)

include(cmake/base/compilers.cmake)
include(cmake/base/warnings.cmake)
include(cmake/base/optimizations.cmake)
include(cmake/base/link.cmake)
