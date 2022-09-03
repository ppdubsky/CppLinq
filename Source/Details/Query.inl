#pragma once

#include "Details/Query.hpp"

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
    auto Query<TEnumerator>::Concatenate(const Query<TNextEnumerator>& nextQuery) -> Query<Enumerators::ConcatenationEnumerator<TEnumerator, TNextEnumerator>>
    {
        return { { enumerator, nextQuery } };
    }

    template <typename TEnumerator>
    template <typename TFunction>
    auto Query<TEnumerator>::ForEach(const TFunction function) -> Query<Enumerators::ForEachEnumerator<TEnumerator, TFunction>>
    {
        return { { enumerator, function } };
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::OrderBy() -> Query<Enumerators::OrderEnumerator<std::vector<ValueType>>>
    {
        return { { ToVector() } };
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::Reverse() -> Query<Enumerators::ReverseEnumerator<std::vector<ValueType>>>
    {
        return { { ToVector() } };
    }

    template <typename TEnumerator>
    template <typename TSelector>
    auto Query<TEnumerator>::Select(const TSelector selector) -> Query<Enumerators::SelectEnumerator<TEnumerator, TSelector>>
    {
        return { { enumerator, selector } };
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::Skip(const std::uint32_t count) -> Query<Enumerators::SkipEnumerator<TEnumerator>>
    {
        return { { enumerator, count } };
    }

    template <typename TEnumerator>
    template <typename TNewType>
    auto Query<TEnumerator>::StaticCast() -> Query<Enumerators::StaticCastEnumerator<TEnumerator, TNewType>>
    {
        return { { enumerator } };
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::Take(const std::uint32_t count) -> Query<Enumerators::TakeEnumerator<TEnumerator>>
    {
        return { { enumerator, count } };
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::ToVector() -> std::vector<ValueType>
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
    auto Query<TEnumerator>::Where(const TPredicate predicate) -> Query<Enumerators::WhereEnumerator<TEnumerator, TPredicate>>
    {
        return { { enumerator, predicate } };
    }
}