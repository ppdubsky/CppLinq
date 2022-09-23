#pragma once

#include "Details/Enumerators/ConcatenationEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TFirstEnumerator, typename TSecondEnumerator>
    ConcatenationEnumerator<TFirstEnumerator, TSecondEnumerator>::ConcatenationEnumerator(const TFirstEnumerator firstEnumerator, const TSecondEnumerator& secondEnumerator) :
        Base(firstEnumerator),
        secondEnumerator(secondEnumerator)
    {
    }

    template <typename TFirstEnumerator, typename TSecondEnumerator>
    auto ConcatenationEnumerator<TFirstEnumerator, TSecondEnumerator>::GetCurrent() -> Base::ValueType
    {
        return Base::HasCurrent() ? Base::GetCurrent() : secondEnumerator.GetCurrent();
    }

    template <typename TFirstEnumerator, typename TSecondEnumerator>
    auto ConcatenationEnumerator<TFirstEnumerator, TSecondEnumerator>::HasCurrent() -> bool
    {
        return Base::HasCurrent() || secondEnumerator.HasCurrent();
    }

    template <typename TFirstEnumerator, typename TSecondEnumerator>
    void ConcatenationEnumerator<TFirstEnumerator, TSecondEnumerator>::MoveNext()
    {
        if (Base::HasCurrent())
        {
            Base::MoveNext();
        }
        else
        {
            secondEnumerator.MoveNext();
        }
    }
}