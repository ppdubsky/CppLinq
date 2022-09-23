#pragma once

#include "Details/Enumerators/ZipEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TZipEnumerator, typename TResultSelector>
    ZipEnumerator<TEnumerator, TZipEnumerator, TResultSelector>::ZipEnumerator(const TEnumerator enumerator, const TZipEnumerator zipEnumerator, const TResultSelector resultSelector) :
        Base(enumerator),
        resultSelector(resultSelector),
        zipEnumerator(zipEnumerator)
    {
    }

    template <typename TEnumerator, typename TZipEnumerator, typename TResultSelector>
    auto ZipEnumerator<TEnumerator, TZipEnumerator, TResultSelector>::GetCurrent() -> ValueType
    {
        return resultSelector(Base::GetCurrent(), zipEnumerator.GetCurrent());
    }
    
    template <typename TEnumerator, typename TZipEnumerator, typename TResultSelector>
    auto ZipEnumerator<TEnumerator, TZipEnumerator, TResultSelector>::HasCurrent() -> bool
    {
        return Base::HasCurrent() && zipEnumerator.HasCurrent();
    }

    template <typename TEnumerator, typename TZipEnumerator, typename TResultSelector>
    void ZipEnumerator<TEnumerator, TZipEnumerator, TResultSelector>::MoveNext()
    {
        Base::MoveNext();
        zipEnumerator.MoveNext();
    }
}