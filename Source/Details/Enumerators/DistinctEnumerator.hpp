#pragma once

#include "Details/Enumerators/DistinctEnumerator.Forward.hpp"

#include <cstdint>
#include <unordered_set>

#include "Details/Containers/DoNothingHasher.hpp"
#include "Details/Enumerators/EnumeratorWrapper.hpp"
#include "Details/TypeTraits/FunctionReturnTypeProvider.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TKeySelector, typename TKeyComparer>
    struct DistinctEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;
        using KeyType = TypeTraits::FunctionReturnTypeProvider<TKeySelector, typename Base::ValueType>::ReturnType;
        using HasherType = Containers::DoNothingHasher<KeyType>;
        using ContainerType = std::unordered_set<KeyType, HasherType, TKeyComparer>;

        DistinctEnumerator(const TEnumerator enumerator, const TKeySelector keySelector, const TKeyComparer keyComparer);

        auto GetCurrent() -> Base::ValueType;
        void MoveNext();

    private:
        void EnsureEnumeratorIsReady();

        static constexpr std::uint32_t bucketCount = 1U;

        ContainerType container;
        bool isReady{ false };
        TKeySelector keySelector;
    };
}