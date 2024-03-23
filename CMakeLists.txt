cmake_minimum_required(VERSION 3.27)

set(MCU atmega88pa)
set(FREQ 8000000UL)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/avr-gcc.cmake")

project(avr_atmega88pa_project VERSION 1.0.0 LANGUAGES C)

add_subdirectory(src)
