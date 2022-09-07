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
        if (!HasCurrent())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        typename Base::ValueType current;

        if (Base::HasCurrent())
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
    auto AppendEnumerator<TEnumerator>::HasCurrent() -> bool
    {
        return Base::HasCurrent() || !isAppended;
    }

    template <typename TEnumerator>
    void AppendEnumerator<TEnumerator>::MoveNext()
    {
        if (!HasCurrent())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        if (Base::HasCurrent())
        {
            Base::MoveNext();
        }
        else
        {
            isAppended = true;
        }
    }
}