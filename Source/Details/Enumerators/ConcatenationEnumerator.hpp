#pragma once

#include "Details/Enumerators/ConcatenationEnumerator.Forward.hpp"

#include "Details/Enumerators/EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TNextEnumerator>
    struct ConcatenationEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;

        ConcatenationEnumerator(const TEnumerator enumerator, const TNextEnumerator& nextEnumerator);

        auto GetCurrent() -> Base::ValueType;
        auto HasCurrent() -> bool;
        void MoveNext();

    private:
        TNextEnumerator nextEnumerator;
    };
}