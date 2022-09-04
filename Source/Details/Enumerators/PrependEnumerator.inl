#pragma once

#include "Details/Enumerators/PrependEnumerator.hpp"

#include "Exceptions/FinishedEnumeratorException.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    PrependEnumerator<TEnumerator>::PrependEnumerator(const TEnumerator enumerator, const Base::ValueType& value) :
        Base(enumerator),
        value(value)
    {
    }

    template <typename TEnumerator>
    auto PrependEnumerator<TEnumerator>::GetCurrent() -> Base::ValueType
    {
        if (IsFinished())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        typename Base::ValueType current;

        if (isPrepended)
        {
            current = Base::GetCurrent();
        }
        else
        {
            current = value;
        }

        return current;
    }

    template <typename TEnumerator>
    auto PrependEnumerator<TEnumerator>::IsFinished() -> bool
    {
        return Base::IsFinished() && isPrepended;
    }

    template <typename TEnumerator>
    void PrependEnumerator<TEnumerator>::MoveNext()
    {
        if (IsFinished())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        if (isPrepended)
        {
            Base::MoveNext();
        }
        else
        {
            isPrepended = true;
        }
    }
}