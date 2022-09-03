#pragma once

#include "Details/Enumerators/OrderEnumerator.hpp"

#include <algorithm>

namespace CppLinq::Details::Enumerators
{
    template <typename TContainer>
    OrderEnumerator<TContainer>::OrderEnumerator(const TContainer& container) :
        container(container)
    {
        SortContainer();
    }

    template <typename TContainer>
    auto OrderEnumerator<TContainer>::GetCurrent() -> const ValueType&
    {
        if (IsFinished())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        return *begin;
    }

    template <typename TContainer>
    auto OrderEnumerator<TContainer>::IsFinished() -> bool
    {
        return begin == end;
    }

    template <typename TContainer>
    void OrderEnumerator<TContainer>::MoveNext()
    {
        if (IsFinished())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        ++begin;
    }

    template <typename TContainer>
    void OrderEnumerator<TContainer>::SortContainer()
    {
        std::sort(container.begin(), container.end());

        begin = container.cbegin();
        end = container.cend();
    }
}