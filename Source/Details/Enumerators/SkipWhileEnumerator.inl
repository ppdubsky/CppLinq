#pragma once

#include "Details/Enumerators/SkipWhileEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TPredicate>
    SkipWhileEnumerator<TEnumerator, TPredicate>::SkipWhileEnumerator(const TEnumerator enumerator, const TPredicate predicate) :
        Base(enumerator),
        predicate(predicate)
    {
    }

    template <typename TEnumerator, typename TPredicate>
    void SkipWhileEnumerator<TEnumerator, TPredicate>::EnsureEnumeratorIsReady()
    {
        if (!isReady)
        {
            while (Base::HasCurrent() && predicate(Base::GetCurrent()))
            {
                Base::MoveNext();
            }

            isReady = true;
        }
    }

    template <typename TEnumerator, typename TPredicate>
    auto SkipWhileEnumerator<TEnumerator, TPredicate>::GetCurrent() -> Base::ValueType
    {
        EnsureEnumeratorIsReady();

        return Base::GetCurrent();
    }

    template <typename TEnumerator, typename TPredicate>
    auto SkipWhileEnumerator<TEnumerator, TPredicate>::HasCurrent() -> bool
    {
        EnsureEnumeratorIsReady();

        return Base::HasCurrent();
    }

    template <typename TEnumerator, typename TPredicate>
    void SkipWhileEnumerator<TEnumerator, TPredicate>::MoveNext()
    {
        EnsureEnumeratorIsReady();

        Base::MoveNext();
    }
}