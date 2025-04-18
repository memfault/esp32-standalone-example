# The following lines of boilerplate have to be in your project's CMakeLists
# in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME memfault-esp32-demo-app)
set(CMAKE_PROJECT_NAME ${PROJECT_NAME})

include($ENV{IDF_PATH}/tools/cmake/version.cmake OPTIONAL)

# This contains the implementation for the led_strip driver. In ESP-IDF v5 it
# moved to a "managed component" and no longer needs to be manually added.
if(DEFINED IDF_VERSION_MAJOR)
  if(IDF_VERSION_MAJOR VERSION_LESS 5)
    set(EXTRA_COMPONENT_DIRS $ENV{IDF_PATH}/examples/common_components/led_strip)
  endif()
endif()

# Pull in the Memfault SDK if we're not building as a component, indicated by
# the absence of the MEMFAULT_SDK_COMPONENT env var.
if(NOT DEFINED ENV{MEMFAULT_SDK_COMPONENT})
  # Look for the Memfault SDK in a subdirectory first, when this app is used
  # standalone (not from within the Memfault SDK)
  get_filename_component(memfault_firmware_sdk_dir third-party/memfault-firmware-sdk ABSOLUTE)
  if(NOT EXISTS ${memfault_firmware_sdk_dir})
    get_filename_component(memfault_firmware_sdk_dir ../../../../ ABSOLUTE)
  endif()
  include(${memfault_firmware_sdk_dir}/ports/esp_idf/memfault.cmake)
endif()

# NOTE: This include also applies global compiler options, make sure
# this happens first before defining other targets!
# The esp-idf project() macro creates a project_name.elf target:
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

# Wrap the mbedtls netif read/write functions, for instrumentation.
# These MUST be before the project() function below, or they are ignored
if(IDF_VERSION_MAJOR VERSION_GREATER_EQUAL 4)
  idf_build_set_property(LINK_OPTIONS "-Wl,--wrap=mbedtls_net_send,--wrap=mbedtls_net_recv" APPEND)
endif()

project(${PROJECT_NAME})

# Enable a compilation error if any deprecated APIs are used. This helps detect
# bleeding edge changes in the ESP-IDF.
if (IDF_VERSION_MAJOR VERSION_GREATER_EQUAL 5)
  idf_build_set_property(COMPILE_OPTIONS "-Werror=deprecated-declarations" APPEND)
endif()

# Check for invalid partition table configurations
if (
  CONFIG_APP_MEMFAULT_TRANSPORT_HTTP AND
  NOT CONFIG_PARTITION_TABLE_CUSTOM_FILENAME STREQUAL "partitions_example.csv"
)
  message(WARNING "Data transport is HTTP but using partition table ${CONFIG_PARTITION_TABLE_CUSTOM_FILENAME}")
  set(INVALID_PARTITION_TABLE true)
elseif(
  CONFIG_APP_MEMFAULT_TRANSPORT_MQTT AND
  NOT CONFIG_PARTITION_TABLE_CUSTOM_FILENAME STREQUAL "partitions_example_mqtt.csv"
)
  message(WARNING "Data transport is MQTT but using partition table ${CONFIG_PARTITION_TABLE_CUSTOM_FILENAME}")
  set(INVALID_PARTITION_TABLE true)
endif()

if (INVALID_PARTITION_TABLE)
  message(FATAL_ERROR
    "Invalid partition table configuration, check CONFIG_APP_MEMFAULT_TRANSPORT configs.\
    If this error occurs repeatedly run `idf.py fullclean && rm sdkconfig`"
  )
endif()
