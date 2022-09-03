#pragma once

#include "Details/Enumerators/OrderEnumerator.hpp"
#include "Exceptions/FinishedEnumeratorException.hpp"

#include <algorithm>

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    OrderEnumerator<TEnumerator>::OrderEnumerator(const Query<TEnumerator>& query) :
        query(query)
    {
    }

    template <typename TEnumerator>
    void OrderEnumerator<TEnumerator>::EnsureEnumeratorIsReady()
    {
        if (!isReady)
        {
            container = query.ToVector();

            std::sort(container.begin(), container.end());

            begin = container.cbegin();
            end = container.cend();

            isReady = true;
        }
    }

    template <typename TEnumerator>
    auto OrderEnumerator<TEnumerator>::GetCurrent() -> const ValueType&
    {
        EnsureEnumeratorIsReady();

        if (IsFinished())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        return *begin;
    }

    template <typename TEnumerator>
    auto OrderEnumerator<TEnumerator>::IsFinished() -> bool
    {
        EnsureEnumeratorIsReady();

        return begin == end;
    }

    template <typename TEnumerator>
    void OrderEnumerator<TEnumerator>::MoveNext()
    {
        EnsureEnumeratorIsReady();

        if (IsFinished())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        ++begin;
    }
}