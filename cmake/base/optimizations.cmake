if (USING_MSVC)
    set(OPTIMIZATIONS)
elseif (USING_CLANG)
    set(OPTIMIZATIONS -O3)
elseif (USING_GCC)
    set(OPTIMIZATIONS -O3)
endif()

target_compile_options(
    base
    INTERFACE
        ${OPTIMIZATIONS}
)
