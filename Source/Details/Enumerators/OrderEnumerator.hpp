#pragma once

#include <algorithm>

#include "Exceptions/FinishedEnumeratorException.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TContainer, typename TIterator = typename TContainer::const_iterator>
    struct OrderEnumerator final
    {
        using ValueType = typename TContainer::value_type;

        OrderEnumerator(const TContainer& container) :
            container(container)
        {
            SortContainer();
        }

        auto GetCurrent() -> const ValueType&
        {
            if (IsFinished())
            {
                throw Exceptions::FinishedEnumeratorException();
            }

            return *begin;
        }

        auto IsFinished() -> bool
        {
            return begin == end;
        }

        void MoveNext()
        {
            if (IsFinished())
            {
                throw Exceptions::FinishedEnumeratorException();
            }

            ++begin;
        }

    private:
        void SortContainer()
        {
            std::sort(container.begin(), container.end());

            begin = container.cbegin();
            end = container.cend();
        }

        TIterator begin;
        TContainer container;
        TIterator end;
    };
}