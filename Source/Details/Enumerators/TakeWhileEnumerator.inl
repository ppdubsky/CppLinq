#pragma once

#include "Details/Enumerators/TakeWhileEnumerator.hpp"

#include "Exceptions/FinishedEnumeratorException.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TPredicate>
    TakeWhileEnumerator<TEnumerator, TPredicate>::TakeWhileEnumerator(const TEnumerator enumerator, const TPredicate predicate) :
        Base(enumerator),
        predicate(predicate)
    {
    }

    template <typename TEnumerator, typename TPredicate>
    auto TakeWhileEnumerator<TEnumerator, TPredicate>::GetCurrent() -> Base::ValueType
    {
        if (!HasCurrent())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        return Base::GetCurrent();
    }

    template <typename TEnumerator, typename TPredicate>
    auto TakeWhileEnumerator<TEnumerator, TPredicate>::HasCurrent() -> bool
    {
        return Base::HasCurrent() && predicate(Base::GetCurrent());
    }

    template <typename TEnumerator, typename TPredicate>
    void TakeWhileEnumerator<TEnumerator, TPredicate>::MoveNext()
    {
        if (!HasCurrent())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        Base::MoveNext();
    }
}