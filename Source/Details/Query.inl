#pragma once

#include "Details/Query.hpp"

#include "Details/Enumerators/ConcatenationEnumerator.hpp"
#include "Details/Enumerators/ForEachEnumerator.hpp"
#include "Details/Enumerators/IteratorEnumerator.hpp"
#include "Details/Enumerators/OrderEnumerator.hpp"
#include "Details/Enumerators/ReverseEnumerator.hpp"
#include "Details/Enumerators/SelectEnumerator.hpp"
#include "Details/Enumerators/SkipEnumerator.hpp"
#include "Details/Enumerators/StaticCastEnumerator.hpp"
#include "Details/Enumerators/TakeEnumerator.hpp"
#include "Details/Enumerators/WhereEnumerator.hpp"
#include "Details/Loops/LoopIterator.hpp"
#include "Details/Loops/LoopIteratorSentinel.hpp"

namespace CppLinq::Details
{
    template <typename TEnumerator>
    Query<TEnumerator>::Query(const TEnumerator enumerator) :
        enumerator(enumerator)
    {
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::begin() const -> Loops::LoopIterator<TEnumerator>
    {
        return { enumerator };
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::end() const -> Loops::LoopIteratorSentinel
    {
        return {};
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::GetEnumerator() -> TEnumerator&
    {
        return enumerator;
    }

    template <typename TEnumerator>
    template <typename TNextEnumerator>
    auto Query<TEnumerator>::Concatenate(const Query<TNextEnumerator>& nextQuery) const -> Query<Enumerators::ConcatenationEnumerator<TEnumerator, TNextEnumerator>>
    {
        return { { enumerator, nextQuery } };
    }

    template <typename TEnumerator>
    template <typename TFunction>
    auto Query<TEnumerator>::ForEach(const TFunction function) const -> Query<Enumerators::ForEachEnumerator<TEnumerator, TFunction>>
    {
        return { { enumerator, function } };
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::OrderBy() const -> Query<Enumerators::OrderEnumerator<TEnumerator>>
    {
        return { { *this } };
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::Reverse() const -> Query<Enumerators::ReverseEnumerator<TEnumerator>>
    {
        return { { *this } };
    }

    template <typename TEnumerator>
    template <typename TSelector>
    auto Query<TEnumerator>::Select(const TSelector selector) const -> Query<Enumerators::SelectEnumerator<TEnumerator, TSelector>>
    {
        return { { enumerator, selector } };
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::Skip(const std::uint32_t count) const -> Query<Enumerators::SkipEnumerator<TEnumerator>>
    {
        return { { enumerator, count } };
    }

    template <typename TEnumerator>
    template <typename TNewType>
    auto Query<TEnumerator>::StaticCast() const -> Query<Enumerators::StaticCastEnumerator<TEnumerator, TNewType>>
    {
        return { { enumerator } };
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::Take(const std::uint32_t count) const -> Query<Enumerators::TakeEnumerator<TEnumerator>>
    {
        return { { enumerator, count } };
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::ToVector() const -> std::vector<ValueType>
    {
        std::vector<ValueType> items;

        TEnumerator enumeratorCopy = enumerator;
        while (!enumeratorCopy.IsFinished())
        {
            items.push_back(enumeratorCopy.GetCurrent());

            enumeratorCopy.MoveNext();
        }

        return items;
    }

    template <typename TEnumerator>
    template <typename TPredicate>
    auto Query<TEnumerator>::Where(const TPredicate predicate) const -> Query<Enumerators::WhereEnumerator<TEnumerator, TPredicate>>
    {
        return { { enumerator, predicate } };
    }
}