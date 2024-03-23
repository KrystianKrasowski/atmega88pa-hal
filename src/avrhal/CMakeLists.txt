set(SOURCES
    gpio.c
    spi.c
    t0pwm.c
    t1ctc.c
    t1int.c
    t1nrm.c)

add_library(avrhal STATIC ${SOURCES})
target_include_directories(avrhal PUBLIC "${CMAKE_SOURCE_DIR}/include")