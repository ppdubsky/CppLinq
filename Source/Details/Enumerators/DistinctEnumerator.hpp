#pragma once

#include "Details/Enumerators/DistinctEnumerator.Forward.hpp"

#include <vector>

#include "Details/Enumerators/EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TSelector, typename TComparer>
    struct DistinctEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;
        using KeyType = decltype(std::declval<TSelector>()(std::declval<Base::ValueType>()));
        using ContainerType = std::vector<KeyType>;

        DistinctEnumerator(const TEnumerator enumerator, const TSelector selector, const TComparer comparer);

        auto GetCurrent() -> Base::ValueType;
        void MoveNext();

    private:
        void EnsureEnumeratorIsReady();

        TComparer comparer;
        bool isReady{ false };
        ContainerType keys;
        TSelector selector;
    };
}