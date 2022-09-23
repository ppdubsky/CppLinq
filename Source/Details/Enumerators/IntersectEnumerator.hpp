#pragma once

#include "Details/Enumerators/IntersectEnumerator.Forward.hpp"

#include <cstdint>
#include <type_traits>
#include <unordered_set>

#include "Details/Containers/DoNothingHasher.hpp"
#include "Details/Enumerators/EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TIntersectEnumerator, typename TKeySelector, typename TKeyComparer>
    struct IntersectEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;
        using KeyType = decltype(std::declval<TKeySelector>()(std::declval<Base::ValueType>()));
        using HasherType = Containers::DoNothingHasher<KeyType>;
        using ContainerType = std::unordered_set<KeyType, HasherType, TKeyComparer>;

        IntersectEnumerator(const TEnumerator enumerator, const TIntersectEnumerator intersectEnumerator, const TKeySelector keySelector, const TKeyComparer keyComparer);

        auto GetCurrent() -> Base::ValueType;
        auto HasCurrent() -> bool;
        void MoveNext();

    private:
        void EnsureContainerIsReady();
        void EnsureEnumeratorIsReady();

        static constexpr std::uint32_t bucketCount = 1U;

        ContainerType container;
        TIntersectEnumerator intersectEnumerator;
        bool isContainerReady{ false };
        bool isReady{ false };
        TKeySelector keySelector;
    };
}