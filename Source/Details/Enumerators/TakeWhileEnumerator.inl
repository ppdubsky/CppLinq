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
        if (IsFinished())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        return Base::GetCurrent();
    }

    template <typename TEnumerator, typename TPredicate>
    auto TakeWhileEnumerator<TEnumerator, TPredicate>::IsFinished() -> bool
    {
        return Base::IsFinished() || !predicate(Base::GetCurrent());
    }

    template <typename TEnumerator, typename TPredicate>
    void TakeWhileEnumerator<TEnumerator, TPredicate>::MoveNext()
    {
        if (IsFinished())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        Base::MoveNext();
    }
}