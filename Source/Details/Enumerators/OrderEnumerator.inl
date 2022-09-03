#pragma once

#include "Details/Enumerators/OrderEnumerator.hpp"

#include <algorithm>

namespace CppLinq::Details::Enumerators
{
    template <typename TContainer, typename TIterator>
    OrderEnumerator<TContainer, TIterator>::OrderEnumerator(const TContainer& container) :
        container(container)
    {
        SortContainer();
    }

    template <typename TContainer, typename TIterator>
    auto OrderEnumerator<TContainer, TIterator>::GetCurrent() -> const ValueType&
    {
        if (IsFinished())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        return *begin;
    }

    template <typename TContainer, typename TIterator>
    auto OrderEnumerator<TContainer, TIterator>::IsFinished() -> bool
    {
        return begin == end;
    }

    template <typename TContainer, typename TIterator>
    void OrderEnumerator<TContainer, TIterator>::MoveNext()
    {
        if (IsFinished())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        ++begin;
    }

    template <typename TContainer, typename TIterator>
    void OrderEnumerator<TContainer, TIterator>::SortContainer()
    {
        std::sort(container.begin(), container.end());

        begin = container.cbegin();
        end = container.cend();
    }
}