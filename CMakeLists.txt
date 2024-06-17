cmake_minimum_required(VERSION 3.16.0)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
list(APPEND EXTRA_COMPONENT_DIRS components/golioth-firmware-sdk/port/esp_idf/components)
project(golioth-pio)
