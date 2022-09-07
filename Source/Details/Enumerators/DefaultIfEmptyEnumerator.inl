#pragma once

#include "Details/Enumerators/DefaultIfEmptyEnumerator.hpp"

#include "Exceptions/FinishedEnumeratorException.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    DefaultIfEmptyEnumerator<TEnumerator>::DefaultIfEmptyEnumerator(const TEnumerator enumerator, const Base::ValueType value) :
        Base(enumerator),
        value(value)
    {
    }

    template <typename TEnumerator>
    auto DefaultIfEmptyEnumerator<TEnumerator>::GetCurrent() -> Base::ValueType
    {
        if (isMovedNext && isEnumeratorEmpty)
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        return isMovedNext
            ? Base::GetCurrent()
            : Base::HasCurrent()
                ? Base::GetCurrent()
                : value;
    }

    template <typename TEnumerator>
    auto DefaultIfEmptyEnumerator<TEnumerator>::HasCurrent() -> bool
    {
        return Base::HasCurrent() || !isMovedNext;
    }

    template <typename TEnumerator>
    void DefaultIfEmptyEnumerator<TEnumerator>::MoveNext()
    {
        if (isMovedNext && isEnumeratorEmpty)
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        if (isMovedNext)
        {
            Base::MoveNext();
        }
        else
        {
            if (Base::HasCurrent())
            {
                Base::MoveNext();

                isEnumeratorEmpty = false;
            }

            isMovedNext = true;
        }
    }
}