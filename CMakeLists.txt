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
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/AggregateMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/AggregateMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/AllMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/AllMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/AnyMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/AnyMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/AppendMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/AppendMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/AverageMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/AverageMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/ChunkMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/ChunkMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/ConcatenateMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/ConcatenateMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/CountMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/CountMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/DefaultIfEmptyMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/DefaultIfEmptyMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/FirstMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/FirstMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/FirstOptionalMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/FirstOptionalMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/FirstOrDefaultMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/FirstOrDefaultMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/ForEachMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/ForEachMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/LastMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/LastMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/LastOptionalMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/LastOptionalMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/LastOrDefaultMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/LastOrDefaultMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/MaximumMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/MaximumMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/MinimumMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/MinimumMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/MixinUtilities.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/MixinUtilities.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/OrderByMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/OrderByMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/PrependMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/PrependMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/QueryMixins.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/ReverseMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/ReverseMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/SelectMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/SelectMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/SingleMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/SingleMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/SingleOptionalMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/SingleOptionalMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/SingleOrDefaultMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/SingleOrDefaultMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/SkipMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/SkipMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/SkipWhileMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/SkipWhileMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/StaticCastMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/StaticCastMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/SumMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/SumMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/TakeMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/TakeMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/TakeWhileMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/TakeWhileMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/ToVectorMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/ToVectorMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/WhereMixin.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Mixins/WhereMixin.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/Query.Forward.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Query.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/Query.inl
        ${PROJECT_SOURCE_DIR}/Source/Details/TypeTraits/EnumeratorTypeProvider.hpp
        ${PROJECT_SOURCE_DIR}/Source/Details/TypeTraits/ValueTypeProvider.hpp
        ${PROJECT_SOURCE_DIR}/Source/Exceptions/ArgumentOutOfRangeException.hpp
        ${PROJECT_SOURCE_DIR}/Source/Exceptions/EmptyCollectionException.hpp
        ${PROJECT_SOURCE_DIR}/Source/Exceptions/FinishedEnumeratorException.hpp
        ${PROJECT_SOURCE_DIR}/Source/Exceptions/MoreThanOneElementException.hpp
)

enable_testing()

add_subdirectory(Modules/GoogleTest)
add_subdirectory(Tests)