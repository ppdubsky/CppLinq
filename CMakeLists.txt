cmake_minimum_required(VERSION 3.8)

set(PROJECT_NAME CppLinq)

project(${PROJECT_NAME} VERSION 0.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(/MD /W4 /WX)
endif()

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(
    ${PROJECT_NAME}
    INTERFACE 
        ${PROJECT_SOURCE_DIR}/Source
)

target_sources(
    ${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/Source/CppLinq.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/ConcatenationEnumerator.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/EnumeratorWrapper.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/ForEachEnumerator.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/IteratorEnumerator.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/OrderEnumerator.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/ReverseEnumerator.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/SelectEnumerator.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/SkipEnumerator.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/StaticCastEnumerator.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/TakeEnumerator.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/WhereEnumerator.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Loops/LoopIterator.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Loops/LoopIteratorSentinel.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Query.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/TypeTraits/ValueTypeProvider.hpp
        ${PROJECT_SOURCE_DIR}/Source/Exceptions/FinishedEnumeratorException.hpp
)

enable_testing()

add_subdirectory(Modules/GoogleTest)
add_subdirectory(Tests)