cmake_minimum_required(VERSION 3.8)

set(PROJECT_NAME CppLinq)

project(${PROJECT_NAME} VERSION 0.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(/MD /W4 /WX)
endif()

enable_testing()

add_subdirectory(Modules/GoogleTest)
add_subdirectory(Tests)