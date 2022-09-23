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
    template <typename TEnumerator, typename TOtherEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TKeyComparer>
    struct InnerJoinEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;
        using KeyType = decltype(std::declval<TLeftKeySelector>()(std::declval<Base::ValueType>()));
        using HasherType = Containers::DoNothingHasher<KeyType>;
        using ContainerType = std::unordered_multimap<KeyType, typename TOtherEnumerator::ValueType, HasherType, TKeyComparer>;
        using ValueType = decltype(std::declval<TResultSelector>()(std::declval<Base::ValueType>(), std::declval<typename TOtherEnumerator::ValueType>()));
        using QueueType = std::queue<ValueType>;

        InnerJoinEnumerator(const TEnumerator enumerator, const TOtherEnumerator otherEnumerator, const TLeftKeySelector leftKeySelector, const TRightKeySelector rightKeySelector, const TResultSelector resultSelector, const TKeyComparer keyComparer);

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
        TLeftKeySelector leftKeySelector;
        TOtherEnumerator otherEnumerator;
        QueueType queue;
        TResultSelector resultSelector;
        TRightKeySelector rightKeySelector;
    };
}