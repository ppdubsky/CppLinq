#pragma once

#include "Details/Enumerators/SelectEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TSelector>
    SelectEnumerator<TEnumerator, TSelector>::SelectEnumerator(const TEnumerator enumerator, const TSelector selector) :
        Base(enumerator),
        selector(selector)
    {
    }

    template <typename TEnumerator, typename TSelector>
    auto SelectEnumerator<TEnumerator, TSelector>::GetCurrent() -> ValueType
    {
        return selector(Base::GetCurrent());
    }
}