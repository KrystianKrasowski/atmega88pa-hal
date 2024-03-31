set(SOURCES
    gpio.c
    spi.c
    timer0.c
    timer0_pwm.c
    timer1.c
    timer1_ctc.c
    timer1_interrupts.c
)

add_library(avrhal STATIC ${SOURCES})
target_include_directories(avrhal PUBLIC "${PROJECT_SOURCE_DIR}/include")