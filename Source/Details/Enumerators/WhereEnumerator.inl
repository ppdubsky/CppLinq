#pragma once

#include "Details/Enumerators/WhereEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TPredicate>
    WhereEnumerator<TEnumerator, TPredicate>::WhereEnumerator(const TEnumerator enumerator, const TPredicate predicate) :
        Base(enumerator),
        predicate(predicate)
    {
    }

    template <typename TEnumerator, typename TPredicate>
    void WhereEnumerator<TEnumerator, TPredicate>::EnsureEnumeratorIsReady()
    {
        if (!isReady)
        {
            while (Base::HasCurrent())
            {
                if (predicate(Base::GetCurrent()))
                {
                    break;
                }
                else
                {
                    Base::MoveNext();
                }
            }

            isReady = true;
        }
    }

    template <typename TEnumerator, typename TPredicate>
    auto WhereEnumerator<TEnumerator, TPredicate>::GetCurrent() -> Base::ValueType
    {
        EnsureEnumeratorIsReady();

        return Base::GetCurrent();
    }

    template <typename TEnumerator, typename TPredicate>
    auto WhereEnumerator<TEnumerator, TPredicate>::HasCurrent() -> bool
    {
        EnsureEnumeratorIsReady();

        return Base::HasCurrent();
    }

    template <typename TEnumerator, typename TPredicate>
    void WhereEnumerator<TEnumerator, TPredicate>::MoveNext()
    {
        EnsureEnumeratorIsReady();

        Base::MoveNext();

        isReady = false;
    }
}