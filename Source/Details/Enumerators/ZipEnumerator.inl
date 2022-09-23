#pragma once

#include "Details/Enumerators/ZipEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TFirstEnumerator, typename TSecondEnumerator, typename TResultSelector>
    ZipEnumerator<TFirstEnumerator, TSecondEnumerator, TResultSelector>::ZipEnumerator(const TFirstEnumerator firstEnumerator, const TSecondEnumerator secondEnumerator, const TResultSelector resultSelector) :
        Base(firstEnumerator),
        resultSelector(resultSelector),
        secondEnumerator(secondEnumerator)
    {
    }

    template <typename TFirstEnumerator, typename TSecondEnumerator, typename TResultSelector>
    auto ZipEnumerator<TFirstEnumerator, TSecondEnumerator, TResultSelector>::GetCurrent() -> ValueType
    {
        return resultSelector(Base::GetCurrent(), secondEnumerator.GetCurrent());
    }
    
    template <typename TFirstEnumerator, typename TSecondEnumerator, typename TResultSelector>
    auto ZipEnumerator<TFirstEnumerator, TSecondEnumerator, TResultSelector>::HasCurrent() -> bool
    {
        return Base::HasCurrent() && secondEnumerator.HasCurrent();
    }

    template <typename TFirstEnumerator, typename TSecondEnumerator, typename TResultSelector>
    void ZipEnumerator<TFirstEnumerator, TSecondEnumerator, TResultSelector>::MoveNext()
    {
        Base::MoveNext();
        secondEnumerator.MoveNext();
    }
}