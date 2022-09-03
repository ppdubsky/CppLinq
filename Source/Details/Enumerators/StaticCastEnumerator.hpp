#pragma once

#include "Details/Enumerators/StaticCastEnumerator.Forward.hpp"

#include "Details/Enumerators/EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TNewType>
    struct StaticCastEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;
        using ValueType = TNewType;

        StaticCastEnumerator(const TEnumerator enumerator);

        auto GetCurrent() -> ValueType;
    };
}