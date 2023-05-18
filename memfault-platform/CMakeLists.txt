idf_component_register(
    SRCS
    memfault_platform_device_info.c

    INCLUDE_DIRS
    .

    REQUIRES
    # Needed by the Memfault component in default configuration. Ideally these
    # would be deps of the Memfault component itself instead.
    esp_https_ota
    esp_partition
    esp_timer
    esp_wifi
    driver
)
