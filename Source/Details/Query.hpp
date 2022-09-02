#pragma once

#include <cstdint>
#include <vector>

#include "Enumerators/ConcatenationEnumerator.hpp"
#include "Enumerators/ForEachEnumerator.hpp"
#include "Enumerators/IteratorEnumerator.hpp"
#include "Enumerators/ReverseEnumerator.hpp"
#include "Enumerators/SelectEnumerator.hpp"
#include "Enumerators/SkipEnumerator.hpp"
#include "Enumerators/StaticCastEnumerator.hpp"
#include "Enumerators/TakeEnumerator.hpp"
#include "Enumerators/WhereEnumerator.hpp"
#include "Loops/LoopIterator.hpp"
#include "Loops/LoopIteratorSentinel.hpp"

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