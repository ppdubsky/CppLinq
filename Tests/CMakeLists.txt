set(TESTS_PROJECT_NAME "${PROJECT_NAME}Tests")

add_executable(
    ${TESTS_PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/Tests/AggregateTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/AllTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/AnyTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/AppendTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/AverageTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/ChunkTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/ConcatenationTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/ContainsTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/CountTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/DefaultIfEmptyTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/DistinctByTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/DistinctTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/ElementAtOptionalTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/ElementAtOrDefaultTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/ElementAtTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/ExceptByTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/ExceptTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/FirstOptionalTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/FirstOrDefaultTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/FirstTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/ForEachTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/IntersectByTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/IntersectTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/LastOptionalTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/LastOrDefaultTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/LastTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/Main.cpp
    ${PROJECT_SOURCE_DIR}/Tests/MaximumTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/MinimumTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/OrderByTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/PrependTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/ReverseTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/SelectManyTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/SelectTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/SequenceEqualTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/SingleOptionalTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/SingleOrDefaultTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/SingleTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/SkipLastTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/SkipLastWhileTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/SkipTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/SkipWhileTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/StaticCastTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/SumTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/TakeLastTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/TakeLastWhileTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/TakeTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/TakeWhileTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/ToVectorTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/UnionByTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/UnionTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/WhereTests.cpp
    ${PROJECT_SOURCE_DIR}/Tests/ZipTests.cpp
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