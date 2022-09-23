#pragma once

#include "Details/Enumerators/RightJoinEnumerator.Forward.hpp"

#include <cstdint>
#include <optional>
#include <queue>
#include <unordered_map>
#include <vector>

#include "Details/Containers/DoNothingHasher.hpp"
#include "Details/Enumerators/EnumeratorWrapper.hpp"
#include "Details/Storage/IndexedValue.hpp"
#include "Details/Storage/UsableValue.hpp"
#include "Details/TypeTraits/FunctionReturnTypeProvider.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TLeftEnumerator, typename TRightEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TKeyComparer>
    struct RightJoinEnumerator final : EnumeratorWrapper<TLeftEnumerator>
    {
        using Base = EnumeratorWrapper<TLeftEnumerator>;
        using KeyType = TypeTraits::FunctionReturnTypeProvider<TLeftKeySelector, typename Base::ValueType>::ReturnType;
        using HasherType = Containers::DoNothingHasher<KeyType>;
        using ContainerType = std::unordered_multimap<KeyType, Storage::IndexedValue<typename TRightEnumerator::ValueType>, HasherType, TKeyComparer>;
        using ValueType = TypeTraits::FunctionReturnTypeProvider<TResultSelector, std::optional<typename Base::ValueType>, typename TRightEnumerator::ValueType>::ReturnType;
        using QueueType = std::queue<ValueType>;
        using VectorType = std::vector<Storage::UsableValue<typename TRightEnumerator::ValueType>>;

        RightJoinEnumerator(const TLeftEnumerator leftEnumerator, const TRightEnumerator rightEnumerator, const TLeftKeySelector leftKeySelector, const TRightKeySelector rightKeySelector, const TResultSelector resultSelector, const TKeyComparer keyComparer);

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
        VectorType usedValues;
    };
}