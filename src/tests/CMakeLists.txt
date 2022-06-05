add_executable(test1)

target_sources(
    test1
    PRIVATE
        test1.c
)

target_link_libraries(
    test1
    PRIVATE
        cemdutil
)
