#pragma once

#include "Details/Enumerators/SkipLastEnumerator.hpp"

#include "Exceptions/FinishedEnumeratorException.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    SkipLastEnumerator<TEnumerator>::SkipLastEnumerator(const TEnumerator enumerator, const std::uint32_t count) :
        Base(enumerator),
        count(count)
    {
    }

    template <typename TEnumerator>
    void SkipLastEnumerator<TEnumerator>::EnsureEnumeratorIsReady()
    {
        if (!isReady)
        {
            while (count > 0U && Base::HasCurrent())
            {
                container.push(Base::GetCurrent());

                Base::MoveNext();

                --count;
            }

            isReady = true;
        }
    }

    template <typename TEnumerator>
    auto SkipLastEnumerator<TEnumerator>::GetCurrent() -> Base::ValueType
    {
        EnsureEnumeratorIsReady();

        if (!Base::HasCurrent())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        return container.empty() ? Base::GetCurrent() : container.front();
    }

    template <typename TEnumerator>
    auto SkipLastEnumerator<TEnumerator>::HasCurrent() -> bool
    {
        EnsureEnumeratorIsReady();

        return count == 0U && Base::HasCurrent();
    }

    template <typename TEnumerator>
    void SkipLastEnumerator<TEnumerator>::MoveNext()
    {
        EnsureEnumeratorIsReady();

        if (!container.empty())
        {
            container.pop();
            container.push(Base::GetCurrent());
        }

        Base::MoveNext();
    }
}