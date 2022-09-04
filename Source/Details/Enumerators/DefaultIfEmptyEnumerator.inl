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
            : Base::IsFinished()
                ? value
                : Base::GetCurrent();
    }

    template <typename TEnumerator>
    auto DefaultIfEmptyEnumerator<TEnumerator>::IsFinished() -> bool
    {
        return isMovedNext ? Base::IsFinished() : false;
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
            if (!Base::IsFinished())
            {
                Base::MoveNext();

                isEnumeratorEmpty = false;
            }

            isMovedNext = true;
        }
    }
}