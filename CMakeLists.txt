cmake_minimum_required(VERSION 3.15)
project(cemdutil C)

include(cmake/compilers.cmake)
include(cmake/base_warnings.cmake)

add_subdirectory(include)
add_subdirectory(src)

include(cmake/targets_config.cmake)
