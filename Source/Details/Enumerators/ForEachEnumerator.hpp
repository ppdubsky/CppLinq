#pragma once

#include "Details/Enumerators/ForEachEnumerator.Forward.hpp"

#include "Details/Enumerators/EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TFunction>
    struct ForEachEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;

        ForEachEnumerator(const TEnumerator enumerator, const TFunction function);

        auto GetCurrent() -> typename Base::ValueType;

    private:
        TFunction function;
    };
}