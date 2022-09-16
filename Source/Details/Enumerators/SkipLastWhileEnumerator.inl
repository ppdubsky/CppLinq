#pragma once

#include "Details/Enumerators/SkipLastWhileEnumerator.hpp"

#include "Exceptions/FinishedEnumeratorException.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TPredicate>
    SkipLastWhileEnumerator<TEnumerator, TPredicate>::SkipLastWhileEnumerator(const TEnumerator enumerator, const TPredicate predicate) :
        Base(enumerator),
        predicate(predicate)
    {
    }

    template <typename TEnumerator, typename TPredicate>
    void SkipLastWhileEnumerator<TEnumerator, TPredicate>::EnsureEnumeratorIsReady()
    {
        if (!isReady)
        {
            ContainerType elements;

            while (Base::HasCurrent())
            {
                elements.push(Base::GetCurrent());

                Base::MoveNext();
            }

            while (!elements.empty())
            {
                if (predicate(elements.top()))
                {
                    elements.pop();
                }
                else
                {
                    break;
                }
            }

            while (!elements.empty())
            {
                container.push(elements.top());
                elements.pop();
            }

            isReady = true;
        }
    }

    template <typename TEnumerator, typename TPredicate>
    auto SkipLastWhileEnumerator<TEnumerator, TPredicate>::GetCurrent() -> Base::ValueType
    {
        EnsureEnumeratorIsReady();

        if (container.empty())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        return container.top();
    }

    template <typename TEnumerator, typename TPredicate>
    auto SkipLastWhileEnumerator<TEnumerator, TPredicate>::HasCurrent() -> bool
    {
        EnsureEnumeratorIsReady();

        return !container.empty();
    }

    template <typename TEnumerator, typename TPredicate>
    void SkipLastWhileEnumerator<TEnumerator, TPredicate>::MoveNext()
    {
        EnsureEnumeratorIsReady();

        if (container.empty())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        container.pop();
    }
}