#pragma once

#include "Details/Enumerators/AppendEnumerator.hpp"

#include "Exceptions/FinishedEnumeratorException.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    AppendEnumerator<TEnumerator>::AppendEnumerator(const TEnumerator enumerator, const Base::ValueType& value) :
        Base(enumerator),
        value(value)
    {
    }

    template <typename TEnumerator>
    auto AppendEnumerator<TEnumerator>::GetCurrent() -> Base::ValueType
    {
        if (IsFinished())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        typename Base::ValueType current;

        if (Base::IsFinished())
        {
            current = value;
        }
        else
        {
            current = Base::GetCurrent();
        }

        return current;
    }

    template <typename TEnumerator>
    auto AppendEnumerator<TEnumerator>::IsFinished() -> bool
    {
        return Base::IsFinished() && isAppended;
    }

    template <typename TEnumerator>
    void AppendEnumerator<TEnumerator>::MoveNext()
    {
        if (IsFinished())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        if (Base::IsFinished())
        {
            isAppended = true;
        }
        else
        {
            Base::MoveNext();
        }
    }
}