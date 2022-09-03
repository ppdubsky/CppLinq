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

        Query(const TEnumerator enumerator);

        auto begin() const -> Loops::LoopIterator<TEnumerator>;
        auto end() const -> Loops::LoopIteratorSentinel;

        auto GetEnumerator() -> TEnumerator&;

        template <typename TNextEnumerator>
        auto Concatenate(const Query<TNextEnumerator>& nextQuery) -> Query<Enumerators::ConcatenationEnumerator<TEnumerator, TNextEnumerator>>;
        template <typename TFunction>
        auto ForEach(const TFunction function) -> Query<Enumerators::ForEachEnumerator<TEnumerator, TFunction>>;
        auto OrderBy() -> Query<Enumerators::OrderEnumerator<std::vector<ValueType>>>;
        auto Reverse() -> Query<Enumerators::ReverseEnumerator<std::vector<ValueType>>>;
        template <typename TSelector>
        auto Select(const TSelector selector) -> Query<Enumerators::SelectEnumerator<TEnumerator, TSelector>>;
        auto Skip(const std::uint32_t count) -> Query<Enumerators::SkipEnumerator<TEnumerator>>;
        template <typename TNewType>
        auto StaticCast() -> Query<Enumerators::StaticCastEnumerator<TEnumerator, TNewType>>;
        auto Take(const std::uint32_t count) -> Query<Enumerators::TakeEnumerator<TEnumerator>>;
        auto ToVector() -> std::vector<ValueType>;
        template <typename TPredicate>
        auto Where(const TPredicate predicate) -> Query<Enumerators::WhereEnumerator<TEnumerator, TPredicate>>;

    private:
        TEnumerator enumerator;
    };
}