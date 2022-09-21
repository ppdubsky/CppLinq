function(add_unit_test)
    set(OPTIONS)
    set(ONE_VALUE_ARGUMENTS NAME)
    set(MULTI_VALUE_ARGUMENTS SOURCES)
    cmake_parse_arguments(PARSED_ARGUMENT "${OPTIONS}" "${ONE_VALUE_ARGUMENTS}" "${MULTI_VALUE_ARGUMENTS}" ${ARGN})

    if(NOT PARSED_ARGUMENT_NAME)
        message(FATAL_ERROR "Test name is not specified.")
    endif()

    if(NOT PARSED_ARGUMENT_SOURCES)
        message(FATAL_ERROR "Test sources are not specified.")
    endif()

    set(TESTS_PROJECT_NAME "${PARSED_ARGUMENT_NAME}")

    add_executable(${TESTS_PROJECT_NAME})

    target_sources(
        ${TESTS_PROJECT_NAME}
        PRIVATE
            ${PARSED_ARGUMENT_SOURCES}
            ${PROJECT_SOURCE_DIR}/Tests/Assertions.hpp
            ${PROJECT_SOURCE_DIR}/Tests/Main.cpp
    )

    if(MSVC)
        target_compile_options(
            ${TESTS_PROJECT_NAME}
            PRIVATE
                /W4 /WX
        )
    endif()

    target_include_directories(
        ${TESTS_PROJECT_NAME}
        PRIVATE
            ${CMAKE_BINARY_DIR}/googletest-src/googletest/include
            ${PROJECT_SOURCE_DIR}/Tests
    )

    target_link_libraries(
        ${TESTS_PROJECT_NAME}
        PRIVATE
            ${PROJECT_NAME}
            gtest
            gtest_main
    )

    add_test(${TESTS_PROJECT_NAME}, ${TESTS_PROJECT_NAME})
endfunction()