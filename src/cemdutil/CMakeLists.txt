target_compile_features(
    cemdutil
    PUBLIC
        c_std_17
)

target_sources(
    cemdutil
    PRIVATE
        dstring.c
)
