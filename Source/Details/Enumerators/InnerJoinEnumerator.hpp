#pragma once

#include "Details/Enumerators/InnerJoinEnumerator.Forward.hpp"

#include <cstdint>
#include <queue>
#include <type_traits>
#include <unordered_map>

#include "Details/Containers/DoNothingHasher.hpp"
#include "Details/Enumerators/EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TOtherEnumerator, typename TSelector, typename TOtherSelector, typename TResultSelector, typename TComparer>
    struct InnerJoinEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;
        using KeyType = decltype(std::declval<TSelector>()(std::declval<Base::ValueType>()));
        using HasherType = Containers::DoNothingHasher<KeyType>;
        using ContainerType = std::unordered_multimap<KeyType, typename TOtherEnumerator::ValueType, HasherType, TComparer>;
        using ValueType = decltype(std::declval<TResultSelector>()(std::declval<Base::ValueType>(), std::declval<typename TOtherEnumerator::ValueType>()));
        using QueueType = std::queue<ValueType>;

        InnerJoinEnumerator(const TEnumerator enumerator, const TOtherEnumerator otherEnumerator, const TSelector selector, const TOtherSelector otherSelector, const TResultSelector resultSelector, const TComparer comparer);

        auto GetCurrent() -> ValueType;
        auto HasCurrent() -> bool;
        void MoveNext();

    private:
        void EnsureContainerIsReady();
        void EnsureEnumeratorIsReady();

        static constexpr std::uint32_t bucketCount = 1U;

        ContainerType container;
        bool isContainerReady{ false };
        bool isReady{ false };
        TOtherEnumerator otherEnumerator;
        TOtherSelector otherSelector;
        QueueType queue;
        TResultSelector resultSelector;
        TSelector selector;
    };
}