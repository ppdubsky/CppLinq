cmake_minimum_required(VERSION 3.8)

set(PROJECT_NAME CppLinq)

project(${PROJECT_NAME} VERSION 0.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
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
        ${PROJECT_SOURCE_DIR}/Source/Details/Collections/ConstIteratorProvider.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Collections/ConstIteratorProvider.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Collections/ConstReverseIteratorProvider.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Collections/ConstReverseIteratorProvider.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Collections/DoNothingCollectionStrategy.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Collections/DoNothingCollectionStrategy.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Collections/SortCollectionStrategy.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Collections/SortCollectionStrategy.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Collections/VectorCollectionProvider.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Collections/VectorCollectionProvider.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/AppendEnumerator.Forward.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/AppendEnumerator.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/AppendEnumerator.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/ChunkEnumerator.Forward.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/ChunkEnumerator.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/ChunkEnumerator.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/CollectionEnumerator.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/CollectionEnumerator.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/ConcatenationEnumerator.Forward.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/ConcatenationEnumerator.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/ConcatenationEnumerator.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/DefaultIfEmptyEnumerator.Forward.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/DefaultIfEmptyEnumerator.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/DefaultIfEmptyEnumerator.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/EnumeratorWrapper.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/EnumeratorWrapper.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/ForEachEnumerator.Forward.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/ForEachEnumerator.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/ForEachEnumerator.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/IteratorEnumerator.Forward.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/IteratorEnumerator.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/IteratorEnumerator.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/OrderEnumerator.Forward.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/OrderEnumerator.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/OrderEnumerator.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/PrependEnumerator.Forward.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/PrependEnumerator.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/PrependEnumerator.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/ReverseEnumerator.Forward.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/ReverseEnumerator.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/ReverseEnumerator.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/SelectEnumerator.Forward.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/SelectEnumerator.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/SelectEnumerator.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/SkipEnumerator.Forward.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/SkipEnumerator.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/SkipEnumerator.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/SkipWhileEnumerator.Forward.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/SkipWhileEnumerator.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/SkipWhileEnumerator.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/StaticCastEnumerator.Forward.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/StaticCastEnumerator.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/StaticCastEnumerator.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/TakeEnumerator.Forward.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/TakeEnumerator.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/TakeEnumerator.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/TakeWhileEnumerator.Forward.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/TakeWhileEnumerator.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/TakeWhileEnumerator.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/WhereEnumerator.Forward.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/WhereEnumerator.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Enumerators/WhereEnumerator.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Loops/LoopIterator.Forward.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Loops/LoopIterator.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Loops/LoopIterator.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Loops/LoopIteratorSentinel.Forward.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Loops/LoopIteratorSentinel.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Query.Forward.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Query.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Query.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/TypeTraits/ValueTypeProvider.hpp
        ${PROJECT_SOURCE_DIR}/Source/Exceptions/ArgumentOutOfRangeException.hpp
        ${PROJECT_SOURCE_DIR}/Source/Exceptions/EmptyCollectionException.hpp
        ${PROJECT_SOURCE_DIR}/Source/Exceptions/FinishedEnumeratorException.hpp
        ${PROJECT_SOURCE_DIR}/Source/Exceptions/MoreThanOneElementException.hpp
)

enable_testing()

add_subdirectory(Modules/GoogleTest)
add_subdirectory(Tests)