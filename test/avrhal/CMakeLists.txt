target_link_libraries(avrhal PUBLIC atmega88pa-stub)

set(TEST_SOURCES
    gpio.c
    spi.c
    timer0_pwm.c
    timer0.c
    timer1_ctc.c
    timer1_interrupts.c
    timer1.c
)

foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})

    target_link_libraries(${TEST_NAME} 
        PRIVATE avrhal unity)

    target_include_directories(${TEST_NAME} 
        PUBLIC ${PROJECT_SOURCE_DIR}/test/include)

    add_test(${TEST_NAME} ${TEST_NAME})
endforeach()
