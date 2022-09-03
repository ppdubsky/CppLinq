#pragma once

#include "Details/Enumerators/EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    EnumeratorWrapper<TEnumerator>::EnumeratorWrapper(const TEnumerator enumerator) :
        enumerator(enumerator)
    {
    }

    template <typename TEnumerator>
    auto EnumeratorWrapper<TEnumerator>::GetCurrent() -> ValueType
    {
        return enumerator.GetCurrent();
    }

    template <typename TEnumerator>
    auto EnumeratorWrapper<TEnumerator>::IsFinished() -> bool
    {
        return enumerator.IsFinished();
    }

    template <typename TEnumerator>
    void EnumeratorWrapper<TEnumerator>::MoveNext()
    {
        enumerator.MoveNext();
    }
}