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
        if (!HasCurrent())
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
    auto PrependEnumerator<TEnumerator>::HasCurrent() -> bool
    {
        return Base::HasCurrent() || !isPrepended;
    }

    template <typename TEnumerator>
    void PrependEnumerator<TEnumerator>::MoveNext()
    {
        if (!HasCurrent())
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