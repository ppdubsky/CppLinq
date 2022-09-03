#pragma once

#include <cstdint>
#include <vector>

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TNextEnumerator>
    struct ConcatenationEnumerator;
    template <typename TEnumerator, typename TFunction>
    struct ForEachEnumerator;
    template <typename TIterator>
    struct IteratorEnumerator;
    template <typename TContainer>
    struct OrderEnumerator;
    template <typename TContainer>
    struct ReverseEnumerator;
    template <typename TEnumerator, typename TSelector>
    struct SelectEnumerator;
    template <typename TEnumerator>
    struct SkipEnumerator;
    template <typename TEnumerator, typename TNewType>
    struct StaticCastEnumerator;
    template <typename TEnumerator>
    struct TakeEnumerator;
    template <typename TEnumerator, typename TPredicate>
    struct WhereEnumerator;
}

namespace CppLinq::Details::Loops
{
    template <typename TEnumerator>
    struct LoopIterator;
    struct LoopIteratorSentinel;
}

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