set(TESTS_PROJECT_NAME "${PROJECT_NAME}Tests")

include_directories(${CMAKE_BINARY_DIR}/googletest-src/googletest/include)
include_directories(${PROJECT_SOURCE_DIR}/Source)

add_executable(
    ${TESTS_PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/Tests/Main.cpp
    ${PROJECT_SOURCE_DIR}/Tests/SelectTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/StaticCastTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/TakeTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/WhereTests.cpp
)

target_link_libraries(
    ${TESTS_PROJECT_NAME}
    gtest
    gtest_main
)

add_test(${TESTS_PROJECT_NAME}, ${TESTS_PROJECT_NAME})