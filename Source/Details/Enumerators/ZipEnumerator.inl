#pragma once

#include "Details/Enumerators/ZipEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TZipEnumerator, typename TSelector>
    ZipEnumerator<TEnumerator, TZipEnumerator, TSelector>::ZipEnumerator(const TEnumerator enumerator, const TZipEnumerator zipEnumerator, const TSelector selector) :
        Base(enumerator),
        selector(selector),
        zipEnumerator(zipEnumerator)
    {
    }

    template <typename TEnumerator, typename TZipEnumerator, typename TSelector>
    auto ZipEnumerator<TEnumerator, TZipEnumerator, TSelector>::GetCurrent() -> ValueType
    {
        return selector(Base::GetCurrent(), zipEnumerator.GetCurrent());
    }
    
    template <typename TEnumerator, typename TZipEnumerator, typename TSelector>
    auto ZipEnumerator<TEnumerator, TZipEnumerator, TSelector>::HasCurrent() -> bool
    {
        return Base::HasCurrent() && zipEnumerator.HasCurrent();
    }

    template <typename TEnumerator, typename TZipEnumerator, typename TSelector>
    void ZipEnumerator<TEnumerator, TZipEnumerator, TSelector>::MoveNext()
    {
        Base::MoveNext();
        zipEnumerator.MoveNext();
    }
}