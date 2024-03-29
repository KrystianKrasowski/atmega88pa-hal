set(TEST_SOURCES 
    hal_spi_master_init.c
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
