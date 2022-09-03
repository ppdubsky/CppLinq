#pragma once

#include "Details/Enumerators/StaticCastEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TNewType>
    StaticCastEnumerator<TEnumerator, TNewType>::StaticCastEnumerator(const TEnumerator enumerator) :
        Base(enumerator)
    {
    }

    template <typename TEnumerator, typename TNewType>
    auto StaticCastEnumerator<TEnumerator, TNewType>::GetCurrent() -> ValueType
    {
        return static_cast<TNewType>(Base::GetCurrent());
    }
}