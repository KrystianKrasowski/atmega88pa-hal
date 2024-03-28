find_package(Doxygen)

if (DOXYGEN_FOUND)
    add_custom_target(
        docs
        ${DOXYGEN_EXECUTABLE}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/docs
    )
endif()