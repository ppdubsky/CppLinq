#pragma once

#include "Details/Enumerators/ZipEnumerator.Forward.hpp"

#include <type_traits>

#include "Details/Enumerators/EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TZipEnumerator, typename TSelector>
    struct ZipEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;
        using ValueType = decltype(std::declval<TSelector>()(std::declval<Base::ValueType>(), std::declval<typename TZipEnumerator::ValueType>()));

        ZipEnumerator(const TEnumerator enumerator, const TZipEnumerator zipEnumerator, const TSelector selector);

        auto GetCurrent() -> ValueType;
        auto HasCurrent() -> bool;
        void MoveNext();

    private:
        TSelector selector;
        TZipEnumerator zipEnumerator;
    };
}