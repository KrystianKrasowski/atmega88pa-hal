cmake_minimum_required(VERSION 3.27)

set(MCU atmega88pa)

project(avrhal VERSION 3.1.0 LANGUAGES C)

include(${PROJECT_SOURCE_DIR}/cmake/docs.cmake)

option(ENABLE_TESTS OFF)

add_subdirectory(src)

if(${ENABLE_TESTS})
    include(${PROJECT_SOURCE_DIR}/cmake/test-dependencies.cmake)
    include(CTest)
    enable_testing()
    add_subdirectory(test)
endif()

