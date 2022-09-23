#pragma once

#include "Details/Enumerators/ExceptEnumerator.Forward.hpp"

#include <cstdint>
#include <type_traits>
#include <unordered_set>

#include "Details/Containers/DoNothingHasher.hpp"
#include "Details/Enumerators/EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TFirstEnumerator, typename TSecondEnumerator, typename TKeySelector, typename TKeyComparer>
    struct ExceptEnumerator final : EnumeratorWrapper<TFirstEnumerator>
    {
        using Base = EnumeratorWrapper<TFirstEnumerator>;
        using KeyType = decltype(std::declval<TKeySelector>()(std::declval<Base::ValueType>()));
        using HasherType = Containers::DoNothingHasher<KeyType>;
        using ContainerType = std::unordered_set<KeyType, HasherType, TKeyComparer>;

        ExceptEnumerator(const TFirstEnumerator firstEnumerator, const TSecondEnumerator secondEnumerator, const TKeySelector keySelector, const TKeyComparer keyComparer);

        auto GetCurrent() -> Base::ValueType;
        auto HasCurrent() -> bool;
        void MoveNext();

    private:
        void EnsureContainerIsReady();
        void EnsureEnumeratorIsReady();

        static constexpr std::uint32_t bucketCount = 1U;

        ContainerType container;
        bool isContainerReady{ false };
        bool isReady{ false };
        TKeySelector keySelector;
        TSecondEnumerator secondEnumerator;
    };
}