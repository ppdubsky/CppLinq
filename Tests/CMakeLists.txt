set(TESTS_PROJECT_NAME "${PROJECT_NAME}Tests")

include_directories(${CMAKE_BINARY_DIR}/googletest-src/googletest/include)

add_executable(
    ${TESTS_PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/Tests/Main.cpp
)

target_link_libraries(
    ${TESTS_PROJECT_NAME}
    gtest
    gtest_main
)

add_test(${TESTS_PROJECT_NAME}, ${TESTS_PROJECT_NAME})