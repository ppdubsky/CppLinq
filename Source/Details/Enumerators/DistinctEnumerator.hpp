#pragma once

#include "Details/Enumerators/DistinctEnumerator.Forward.hpp"

#include <cstdint>
#include <unordered_set>

#include "Details/Containers/DoNothingHasher.hpp"
#include "Details/Enumerators/EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TSelector, typename TComparer>
    struct DistinctEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;
        using KeyType = decltype(std::declval<TSelector>()(std::declval<Base::ValueType>()));
        using HasherType = Containers::DoNothingHasher<KeyType>;
        using ContainerType = std::unordered_set<KeyType, HasherType, TComparer>;

        DistinctEnumerator(const TEnumerator enumerator, const TSelector selector, const TComparer comparer);

        auto GetCurrent() -> Base::ValueType;
        void MoveNext();

    private:
        void EnsureEnumeratorIsReady();

        static constexpr std::uint32_t bucketCount = 1U;

        ContainerType container;
        bool isReady{ false };
        TSelector selector;
    };
}