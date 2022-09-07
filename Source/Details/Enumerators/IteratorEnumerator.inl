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
        if (!HasCurrent())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        return *begin;
    }

    template <typename TIterator>
    auto IteratorEnumerator<TIterator>::HasCurrent() -> bool
    {
        return begin != end;
    }

    template <typename TIterator>
    void IteratorEnumerator<TIterator>::MoveNext()
    {
        if (!HasCurrent())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        ++begin;
    }
}