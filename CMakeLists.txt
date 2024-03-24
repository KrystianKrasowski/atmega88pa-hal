cmake_minimum_required(VERSION 3.27)

set(MCU atmega88pa)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/avr-gcc.cmake")

project(avrhal VERSION 2.0.0 LANGUAGES C)

include(${PROJECT_SOURCE_DIR}/cmake/docs.cmake)

add_subdirectory(src)
