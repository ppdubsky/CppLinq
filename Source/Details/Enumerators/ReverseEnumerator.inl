#pragma once

#include "Details/Enumerators/ReverseEnumerator.hpp"
#include "Exceptions/FinishedEnumeratorException.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    ReverseEnumerator<TEnumerator>::ReverseEnumerator(const Query<TEnumerator>& query) :
        query(query)
    {
    }

    template <typename TEnumerator>
    void ReverseEnumerator<TEnumerator>::EnsureEnumeratorIsReady()
    {
        if (!isReady)
        {
            container = query.ToVector();

            begin = container.crbegin();
            end = container.crend();

            isReady = true;
        }
    }

    template <typename TEnumerator>
    auto ReverseEnumerator<TEnumerator>::GetCurrent() -> const ValueType&
    {
        EnsureEnumeratorIsReady();

        if (IsFinished())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        return *begin;
    }

    template <typename TEnumerator>
    auto ReverseEnumerator<TEnumerator>::IsFinished() -> bool
    {
        EnsureEnumeratorIsReady();

        return begin == end;
    }

    template <typename TEnumerator>
    void ReverseEnumerator<TEnumerator>::MoveNext()
    {
        EnsureEnumeratorIsReady();

        if (IsFinished())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        ++begin;
    }
}