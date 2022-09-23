#pragma once

#include "Details/Enumerators/GroupEnumerator.Forward.hpp"

#include <queue>
#include <unordered_map>
#include <vector>

#include "Details/Containers/DoNothingHasher.hpp"
#include "Details/Enumerators/EnumeratorWrapper.hpp"
#include "Details/TypeTraits/FunctionReturnTypeProvider.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TKeySelector, typename TElementSelector, typename TResultSelector, typename TKeyComparer>
    struct GroupEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;
        using KeyType = TypeTraits::FunctionReturnTypeProvider<TKeySelector, typename Base::ValueType>::ReturnType;
        using ElementType = TypeTraits::FunctionReturnTypeProvider<TElementSelector, typename Base::ValueType>::ReturnType;
        using ElementContainer = std::vector<ElementType>;
        using ValueType = TypeTraits::FunctionReturnTypeProvider<TResultSelector, KeyType, ElementContainer>::ReturnType;
        using KeyContainer = std::vector<KeyType>;
        using HasherType = Containers::DoNothingHasher<KeyType>;
        using GroupContainer = std::unordered_multimap<KeyType, Base::ValueType, HasherType, TKeyComparer>;

        GroupEnumerator(const TEnumerator enumerator, const TKeySelector keySelector, const TElementSelector elementSelector, const TResultSelector resultSelector, const TKeyComparer keyComparer);

        auto GetCurrent() -> ValueType;
        auto HasCurrent() -> bool;
        void MoveNext();

    private:
        void EnsureEnumeratorIsReady();

        static constexpr std::uint32_t bucketCount = 1U;

        TElementSelector elementSelector;
        GroupContainer groupContainer;
        bool isReady{ false };
        KeyContainer keyContainer;
        TKeySelector keySelector;
        TResultSelector resultSelector;
    };
}