set(TESTS_PROJECT_NAME "${PROJECT_NAME}Tests")

add_executable(
    ${TESTS_PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/Tests/AllTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/AnyTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/AppendTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/AverageTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/ConcatenationTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/CountTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/FirstTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/ForEachTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/Main.cpp
    ${PROJECT_SOURCE_DIR}/Tests/MaximumTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/MinimumTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/OrderByTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/PrependTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/ReverseTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/SelectTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/SkipTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/SkipWhileTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/StaticCastTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/SumTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/TakeTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/TakeWhileTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/ToVectorTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/WhereTests.cpp
)

if (MSVC)
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
    ${PROJECT_NAME}
    gtest
    gtest_main
)

add_test(${TESTS_PROJECT_NAME}, ${TESTS_PROJECT_NAME})