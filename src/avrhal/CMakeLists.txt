set(SOURCES
    gpio.c
    spi.c
    timer0.c
    timer0_pwm.c
    timer1.c
    timer1_ctc.c
    timer1_interrupts.c
    timer1_pwm.c
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC avrhal)