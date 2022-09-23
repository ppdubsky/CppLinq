#pragma once

#include "Details/Enumerators/SelectEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TResultSelector>
    SelectEnumerator<TEnumerator, TResultSelector>::SelectEnumerator(const TEnumerator enumerator, const TResultSelector resultSelector) :
        Base(enumerator),
        resultSelector(resultSelector)
    {
    }

    template <typename TEnumerator, typename TResultSelector>
    auto SelectEnumerator<TEnumerator, TResultSelector>::GetCurrent() -> ValueType
    {
        return resultSelector(Base::GetCurrent());
    }
}