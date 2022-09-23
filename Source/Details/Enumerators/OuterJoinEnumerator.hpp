#pragma once

#include "Details/Enumerators/OuterJoinEnumerator.Forward.hpp"

#include <cstdint>
#include <optional>
#include <queue>
#include <type_traits>
#include <unordered_map>
#include <vector>

#include "Details/Containers/DoNothingHasher.hpp"
#include "Details/Enumerators/EnumeratorWrapper.hpp"
#include "Details/Storage/IndexedValue.hpp"
#include "Details/Storage/UsableValue.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TOtherEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TKeyComparer>
    struct OuterJoinEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;
        using KeyType = decltype(std::declval<TLeftKeySelector>()(std::declval<Base::ValueType>()));
        using HasherType = Containers::DoNothingHasher<KeyType>;
        using ContainerType = std::unordered_multimap<KeyType, Storage::IndexedValue<typename TOtherEnumerator::ValueType>, HasherType, TKeyComparer>;
        using ValueType = decltype(std::declval<TResultSelector>()(std::declval<std::optional<Base::ValueType>>(), std::declval<std::optional<typename TOtherEnumerator::ValueType>>()));
        using QueueType = std::queue<ValueType>;
        using VectorType = std::vector<Storage::UsableValue<typename TOtherEnumerator::ValueType>>;

        OuterJoinEnumerator(const TEnumerator enumerator, const TOtherEnumerator otherEnumerator, const TLeftKeySelector leftKeySelector, const TRightKeySelector rightKeySelector, const TResultSelector resultSelector, const TKeyComparer keyComparer);

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
        VectorType usedValues;
    };
}