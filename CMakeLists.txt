# The following lines of boilerplate have to be in your project's CMakeLists
# in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME memfault-esp32-demo-app)
set(CMAKE_PROJECT_NAME ${PROJECT_NAME})

include($ENV{IDF_PATH}/tools/cmake/version.cmake OPTIONAL)

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
