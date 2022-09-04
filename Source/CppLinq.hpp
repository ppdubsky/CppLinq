#pragma once

#include "Details/Collections/ConstIteratorProvider.inl"
#include "Details/Collections/ConstReverseIteratorProvider.inl"
#include "Details/Collections/DoNothingCollectionStrategy.inl"
#include "Details/Collections/SortCollectionStrategy.inl"
#include "Details/Collections/VectorCollectionProvider.inl"
#include "Details/Enumerators/CollectionEnumerator.inl"
#include "Details/Enumerators/ConcatenationEnumerator.inl"
#include "Details/Enumerators/EnumeratorWrapper.inl"
#include "Details/Enumerators/ForEachEnumerator.inl"
#include "Details/Enumerators/IteratorEnumerator.inl"
#include "Details/Enumerators/OrderEnumerator.inl"
#include "Details/Enumerators/ReverseEnumerator.inl"
#include "Details/Enumerators/SelectEnumerator.inl"
#include "Details/Enumerators/SkipEnumerator.inl"
#include "Details/Enumerators/SkipWhileEnumerator.inl"
#include "Details/Enumerators/StaticCastEnumerator.inl"
#include "Details/Enumerators/TakeEnumerator.inl"
#include "Details/Enumerators/TakeWhileEnumerator.inl"
#include "Details/Enumerators/WhereEnumerator.inl"
#include "Details/Loops/LoopIterator.inl"
#include "Details/Query.inl"

namespace CppLinq
{
    template <typename TCollection>
    auto From(const TCollection& collection) -> Details::Query<Details::Enumerators::IteratorEnumerator<typename TCollection::const_iterator>>
    {
        return { { collection.cbegin(), collection.cend() } };
    }

    template <typename T, std::uint32_t TLength>
    auto From(const T (&array)[TLength]) -> Details::Query<Details::Enumerators::IteratorEnumerator<const T*>>
    {
        return { { reinterpret_cast<const T*>(&array), reinterpret_cast<const T*>(&array) + TLength } };
    }
}