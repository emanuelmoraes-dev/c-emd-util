add_executable(test1)

target_sources(
    test1
    PRIVATE
        test1.c
)

target_compile_features(
    test1
    PUBLIC
        c_std_17
)

target_link_libraries(
    test1
    PRIVATE
        cemdutil
)
