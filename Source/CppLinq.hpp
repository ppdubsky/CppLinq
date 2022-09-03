#pragma once

#include "Details/Enumerators/ConcatenationEnumerator.inl"
#include "Details/Enumerators/ContainerEnumerator.inl"
#include "Details/Enumerators/ContainerProviders/VectorContainerProvider.inl"
#include "Details/Enumerators/ContainerStrategies/DoNothingContainerStrategy.inl"
#include "Details/Enumerators/ContainerStrategies/SortContainerStrategy.inl"
#include "Details/Enumerators/EnumeratorWrapper.inl"
#include "Details/Enumerators/ForEachEnumerator.inl"
#include "Details/Enumerators/IteratorEnumerator.inl"
#include "Details/Enumerators/IteratorProviders/ConstIteratorProvider.inl"
#include "Details/Enumerators/IteratorProviders/ConstReverseIteratorProvider.inl"
#include "Details/Enumerators/OrderEnumerator.inl"
#include "Details/Enumerators/ReverseEnumerator.inl"
#include "Details/Enumerators/SelectEnumerator.inl"
#include "Details/Enumerators/SkipEnumerator.inl"
#include "Details/Enumerators/StaticCastEnumerator.inl"
#include "Details/Enumerators/TakeEnumerator.inl"
#include "Details/Enumerators/WhereEnumerator.inl"
#include "Details/Loops/LoopIterator.inl"
#include "Details/Query.inl"

namespace CppLinq
{
    template <typename TContainer>
    auto From(const TContainer& container) -> Details::Query<Details::Enumerators::IteratorEnumerator<typename TContainer::const_iterator>>
    {
        return { { container.cbegin(), container.cend() } };
    }

    template <typename T, std::uint32_t TLength>
    auto From(const T (&array)[TLength]) -> Details::Query<Details::Enumerators::IteratorEnumerator<const T*>>
    {
        return { { reinterpret_cast<const T*>(&array), reinterpret_cast<const T*>(&array) + TLength } };
    }
}