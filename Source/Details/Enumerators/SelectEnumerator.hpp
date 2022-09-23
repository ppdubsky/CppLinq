#pragma once

#include "Details/Enumerators/SelectEnumerator.Forward.hpp"

#include "Details/Enumerators/EnumeratorWrapper.hpp"
#include "Details/TypeTraits/FunctionReturnTypeProvider.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TResultSelector>
    struct SelectEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;
        using ValueType = TypeTraits::FunctionReturnTypeProvider<TResultSelector, typename Base::ValueType>::ReturnType;

        SelectEnumerator(const TEnumerator enumerator, const TResultSelector resultSelector);

        auto GetCurrent() -> ValueType;

    private:
        TResultSelector resultSelector;
    };
}