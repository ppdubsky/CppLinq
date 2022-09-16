#pragma once

#include "Details/Enumerators/TakeLastEnumerator.hpp"

#include "Exceptions/FinishedEnumeratorException.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    TakeLastEnumerator<TEnumerator>::TakeLastEnumerator(const TEnumerator enumerator, const std::uint32_t count) :
        Base(enumerator),
        count(count)
    {
    }

    template <typename TEnumerator>
    void TakeLastEnumerator<TEnumerator>::EnsureEnumeratorIsReady()
    {
        if (!isReady)
        {
            while (Base::HasCurrent())
            {
                container.push(Base::GetCurrent());

                Base::MoveNext();

                if (count == 0U)
                {
                    container.pop();
                }
                else
                {
                    --count;
                }
            }

            isReady = true;
        }
    }

    template <typename TEnumerator>
    auto TakeLastEnumerator<TEnumerator>::GetCurrent() -> Base::ValueType
    {
        EnsureEnumeratorIsReady();

        if (container.empty())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        return container.front();
    }

    template <typename TEnumerator>
    auto TakeLastEnumerator<TEnumerator>::HasCurrent() -> bool
    {
        EnsureEnumeratorIsReady();

        return !container.empty();
    }

    template <typename TEnumerator>
    void TakeLastEnumerator<TEnumerator>::MoveNext()
    {
        EnsureEnumeratorIsReady();

        if (container.empty())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        container.pop();
    }
}