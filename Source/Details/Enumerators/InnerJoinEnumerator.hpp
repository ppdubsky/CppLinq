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
    template <typename TLeftEnumerator, typename TRightEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TKeyComparer>
    struct InnerJoinEnumerator final : EnumeratorWrapper<TLeftEnumerator>
    {
        using Base = EnumeratorWrapper<TLeftEnumerator>;
        using KeyType = decltype(std::declval<TLeftKeySelector>()(std::declval<Base::ValueType>()));
        using HasherType = Containers::DoNothingHasher<KeyType>;
        using ContainerType = std::unordered_multimap<KeyType, typename TRightEnumerator::ValueType, HasherType, TKeyComparer>;
        using ValueType = decltype(std::declval<TResultSelector>()(std::declval<Base::ValueType>(), std::declval<typename TRightEnumerator::ValueType>()));
        using QueueType = std::queue<ValueType>;

        InnerJoinEnumerator(const TLeftEnumerator leftEnumerator, const TRightEnumerator rightEnumerator, const TLeftKeySelector leftKeySelector, const TRightKeySelector rightKeySelector, const TResultSelector resultSelector, const TKeyComparer keyComparer);

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
        QueueType queue;
        TResultSelector resultSelector;
        TRightEnumerator rightEnumerator;
        TRightKeySelector rightKeySelector;
    };
}