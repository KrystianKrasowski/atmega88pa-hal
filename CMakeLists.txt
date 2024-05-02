cmake_minimum_required(VERSION 3.27)

set(MCU atmega88pa)

project(atmega88pa-hal VERSION 3.2.0 LANGUAGES C)

include(${PROJECT_SOURCE_DIR}/cmake/docs.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/dependencies.cmake)

option(ENABLE_TESTS OFF)

add_subdirectory(src)

if(${ENABLE_TESTS})
    include(CTest)
    enable_testing()
    add_subdirectory(test)
endif()

