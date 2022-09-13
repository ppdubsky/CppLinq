#pragma once

#include "Details/Enumerators/ExceptEnumerator.Forward.hpp"

#include <cstdint>
#include <type_traits>
#include <unordered_set>

#include "Details/Containers/DoNothingHasher.hpp"
#include "Details/Enumerators/EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TExceptEnumerator, typename TSelector, typename TComparer>
    struct ExceptEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;
        using KeyType = decltype(std::declval<TSelector>()(std::declval<Base::ValueType>()));
        using HasherType = Containers::DoNothingHasher<KeyType>;
        using ContainerType = std::unordered_set<KeyType, HasherType, TComparer>;

        ExceptEnumerator(const TEnumerator enumerator, const TExceptEnumerator exceptEnumerator, const TSelector selector, const TComparer comparer);

        auto GetCurrent() -> Base::ValueType;
        auto HasCurrent() -> bool;
        void MoveNext();

    private:
        void EnsureContainerIsReady();
        void EnsureEnumeratorIsReady();

        static constexpr std::uint32_t bucketCount = 1U;

        ContainerType container;
        TExceptEnumerator exceptEnumerator;
        bool isContainerReady{ false };
        bool isReady{ false };
        TSelector selector;
    };
}