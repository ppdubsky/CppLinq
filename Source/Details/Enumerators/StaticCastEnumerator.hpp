#pragma once

#include "Details/Enumerators/EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TNewType>
    struct StaticCastEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;
        using ValueType = TNewType;

        StaticCastEnumerator(const TEnumerator enumerator) :
            Base(enumerator)
        {
        }

        auto GetCurrent() -> ValueType
        {
            return static_cast<TNewType>(Base::GetCurrent());
        }
    };
}