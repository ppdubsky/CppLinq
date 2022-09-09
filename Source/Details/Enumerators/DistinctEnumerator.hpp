#pragma once

#include "Details/Enumerators/DistinctEnumerator.Forward.hpp"

#include <unordered_set>

#include "Details/Containers/DoNothingHasher.hpp"
#include "Details/Enumerators/EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TComparer>
    struct DistinctEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;
        using ContainerType = std::unordered_set<Base::ValueType, Containers::DoNothingHasher<typename Base::ValueType>, TComparer>;
        using IteratorType = typename ContainerType::const_iterator;

        DistinctEnumerator(const TEnumerator enumerator, const TComparer comparer);

        auto GetCurrent() -> const Base::ValueType&;
        void MoveNext();

    private:
        void EnsureEnumeratorIsReady();

        TComparer comparer;
        ContainerType container;
        IteratorType current;
        bool isReady{ false };
    };
}