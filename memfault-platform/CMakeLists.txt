idf_component_register(
    SRCS
    memfault_platform_device_info.c

    INCLUDE_DIRS
    .

    # need to explicitly list memfault here on esp-idf <5
    REQUIRES
    memfault
)
