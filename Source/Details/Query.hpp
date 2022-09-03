#pragma once

#include <cstdint>
#include <vector>

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
    struct Query final
    {
        using ValueType = typename TEnumerator::ValueType;

        Query(const TEnumerator enumerator) :
            enumerator(enumerator)
        {
        }

        auto begin() const -> Loops::LoopIterator<TEnumerator>
        {
            return { enumerator };
        }

        auto end() const -> Loops::LoopIteratorSentinel
        {
            return {};
        }

        auto GetEnumerator() -> TEnumerator&
        {
            return enumerator;
        }

        template <typename TNextEnumerator>
        auto Concatenate(const Query<TNextEnumerator>& nextQuery) -> Query<Enumerators::ConcatenationEnumerator<TEnumerator, TNextEnumerator>>
        {
            return { { enumerator, nextQuery } };
        }

        template <typename TFunction>
        auto ForEach(const TFunction function) -> Query<Enumerators::ForEachEnumerator<TEnumerator, TFunction>>
        {
            return { { enumerator, function } };
        }

        auto OrderBy() -> Query<Enumerators::OrderEnumerator<std::vector<ValueType>>>
        {
            return { { ToVector() } };
        }

        auto Reverse() -> Query<Enumerators::ReverseEnumerator<std::vector<ValueType>>>
        {
            return { { ToVector() } };
        }

        template <typename TSelector>
        auto Select(const TSelector selector) -> Query<Enumerators::SelectEnumerator<TEnumerator, TSelector>>
        {
            return { { enumerator, selector } };
        }

        auto Skip(const std::uint32_t count) -> Query<Enumerators::SkipEnumerator<TEnumerator>>
        {
            return { { enumerator, count } };
        }

        template <typename TNewType>
        auto StaticCast() -> Query<Enumerators::StaticCastEnumerator<TEnumerator, TNewType>>
        {
            return { { enumerator } };
        }

        auto Take(const std::uint32_t count) -> Query<Enumerators::TakeEnumerator<TEnumerator>>
        {
            return { { enumerator, count } };
        }

        auto ToVector() -> std::vector<ValueType>
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

        template <typename TPredicate>
        auto Where(const TPredicate predicate) -> Query<Enumerators::WhereEnumerator<TEnumerator, TPredicate>>
        {
            return { { enumerator, predicate } };
        }

    private:
        TEnumerator enumerator;
    };
}