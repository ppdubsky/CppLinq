#pragma once

#include "Details/Enumerators/ZipEnumerator.Forward.hpp"

#include <type_traits>

#include "Details/Enumerators/EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TFirstEnumerator, typename TSecondEnumerator, typename TResultSelector>
    struct ZipEnumerator final : EnumeratorWrapper<TFirstEnumerator>
    {
        using Base = EnumeratorWrapper<TFirstEnumerator>;
        using ValueType = decltype(std::declval<TResultSelector>()(std::declval<Base::ValueType>(), std::declval<typename TSecondEnumerator::ValueType>()));

        ZipEnumerator(const TFirstEnumerator firstEnumerator, const TSecondEnumerator secondEnumerator, const TResultSelector resultSelector);

        auto GetCurrent() -> ValueType;
        auto HasCurrent() -> bool;
        void MoveNext();

    private:
        TResultSelector resultSelector;
        TSecondEnumerator secondEnumerator;
    };
}