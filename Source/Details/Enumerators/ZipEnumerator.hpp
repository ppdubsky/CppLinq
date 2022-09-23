#pragma once

#include "Details/Enumerators/ZipEnumerator.Forward.hpp"

#include "Details/Enumerators/EnumeratorWrapper.hpp"
#include "Details/TypeTraits/FunctionReturnTypeProvider.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TFirstEnumerator, typename TSecondEnumerator, typename TResultSelector>
    struct ZipEnumerator final : EnumeratorWrapper<TFirstEnumerator>
    {
        using Base = EnumeratorWrapper<TFirstEnumerator>;
        using ValueType = TypeTraits::FunctionReturnTypeProvider<TResultSelector, typename Base::ValueType, typename TSecondEnumerator::ValueType>::ReturnType;

        ZipEnumerator(const TFirstEnumerator firstEnumerator, const TSecondEnumerator secondEnumerator, const TResultSelector resultSelector);

        auto GetCurrent() -> ValueType;
        auto HasCurrent() -> bool;
        void MoveNext();

    private:
        TResultSelector resultSelector;
        TSecondEnumerator secondEnumerator;
    };
}