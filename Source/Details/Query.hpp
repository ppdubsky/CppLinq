#pragma once

#include "Details/Query.Forward.hpp"

#include <cstdint>
#include <vector>

#include "Details/Enumerators/AppendEnumerator.Forward.hpp"
#include "Details/Enumerators/ConcatenationEnumerator.Forward.hpp"
#include "Details/Enumerators/ForEachEnumerator.Forward.hpp"
#include "Details/Enumerators/IteratorEnumerator.Forward.hpp"
#include "Details/Enumerators/OrderEnumerator.Forward.hpp"
#include "Details/Enumerators/PrependEnumerator.Forward.hpp"
#include "Details/Enumerators/ReverseEnumerator.Forward.hpp"
#include "Details/Enumerators/SelectEnumerator.Forward.hpp"
#include "Details/Enumerators/SkipEnumerator.Forward.hpp"
#include "Details/Enumerators/SkipWhileEnumerator.Forward.hpp"
#include "Details/Enumerators/StaticCastEnumerator.Forward.hpp"
#include "Details/Enumerators/TakeEnumerator.Forward.hpp"
#include "Details/Enumerators/TakeWhileEnumerator.Forward.hpp"
#include "Details/Enumerators/WhereEnumerator.Forward.hpp"
#include "Details/Loops/LoopIterator.Forward.hpp"
#include "Details/Loops/LoopIteratorSentinel.Forward.hpp"

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

        template <typename TPredicate>
        auto All(const TPredicate predicate) const -> bool;
        template <typename TPredicate>
        auto Any(const TPredicate predicate) const -> bool;
        auto Append(const ValueType& value) const -> Query<Enumerators::AppendEnumerator<TEnumerator>>;
        auto Average() const -> ValueType;
        template <typename TNextEnumerator>
        auto Concatenate(const Query<TNextEnumerator>& nextQuery) const -> Query<Enumerators::ConcatenationEnumerator<TEnumerator, TNextEnumerator>>;
        auto Count() const -> std::uint32_t;
        template <typename TPredicate>
        auto Count(const TPredicate predicate) const -> std::uint32_t;
        auto First() const -> ValueType;
        template <typename TPredicate>
        auto First(const TPredicate predicate) const -> ValueType;
        template <typename TFunction>
        auto ForEach(const TFunction function) const -> Query<Enumerators::ForEachEnumerator<TEnumerator, TFunction>>;
        auto Last() const -> ValueType;
        template <typename TPredicate>
        auto Last(const TPredicate predicate) const -> ValueType;
        auto Maximum() const -> ValueType;
        auto Minimum() const -> ValueType;
        auto OrderBy() const -> Query<Enumerators::OrderEnumerator<TEnumerator>>;
        auto Prepend(const ValueType& value) const -> Query<Enumerators::PrependEnumerator<TEnumerator>>;
        auto Reverse() const -> Query<Enumerators::ReverseEnumerator<TEnumerator>>;
        template <typename TSelector>
        auto Select(const TSelector selector) const -> Query<Enumerators::SelectEnumerator<TEnumerator, TSelector>>;
        auto Skip(const std::uint32_t count) const -> Query<Enumerators::SkipEnumerator<TEnumerator>>;
        template <typename TPredicate>
        auto SkipWhile(const TPredicate predicate) const -> Query<Enumerators::SkipWhileEnumerator<TEnumerator, TPredicate>>;
        template <typename TNewType>
        auto StaticCast() const -> Query<Enumerators::StaticCastEnumerator<TEnumerator, TNewType>>;
        auto Sum() const -> ValueType;
        auto Take(const std::uint32_t count) const -> Query<Enumerators::TakeEnumerator<TEnumerator>>;
        template <typename TPredicate>
        auto TakeWhile(const TPredicate predicate) const -> Query<Enumerators::TakeWhileEnumerator<TEnumerator, TPredicate>>;
        auto ToVector() const -> std::vector<ValueType>;
        template <typename TPredicate>
        auto Where(const TPredicate predicate) const -> Query<Enumerators::WhereEnumerator<TEnumerator, TPredicate>>;

    private:
        auto GetBound(const bool isMaximum) const -> ValueType;

        TEnumerator enumerator;
    };
}