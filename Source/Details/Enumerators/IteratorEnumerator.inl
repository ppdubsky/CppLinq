#pragma once

#include "Details/Enumerators/IteratorEnumerator.hpp"

#include "Exceptions/FinishedEnumeratorException.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TIterator>
    IteratorEnumerator<TIterator>::IteratorEnumerator(const TIterator begin, const TIterator end) :
        begin(begin),
        end(end)
    {
    }

    template <typename TIterator>
    auto IteratorEnumerator<TIterator>::GetCurrent() -> const ValueType&
    {
        if (IsFinished())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        return *begin;
    }

    template <typename TIterator>
    auto IteratorEnumerator<TIterator>::IsFinished() -> bool
    {
        return begin == end;
    }

    template <typename TIterator>
    void IteratorEnumerator<TIterator>::MoveNext()
    {
        if (IsFinished())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        ++begin;
    }
}