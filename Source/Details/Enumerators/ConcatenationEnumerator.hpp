#pragma once

#include "Details/Enumerators/ConcatenationEnumerator.Forward.hpp"

#include "Details/Enumerators/EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TFirstEnumerator, typename TSecondEnumerator>
    struct ConcatenationEnumerator final : EnumeratorWrapper<TFirstEnumerator>
    {
        using Base = EnumeratorWrapper<TFirstEnumerator>;

        ConcatenationEnumerator(const TFirstEnumerator firstEnumerator, const TSecondEnumerator secondEnumerator);

        auto GetCurrent() -> Base::ValueType;
        auto HasCurrent() -> bool;
        void MoveNext();

    private:
        TSecondEnumerator secondEnumerator;
    };
}