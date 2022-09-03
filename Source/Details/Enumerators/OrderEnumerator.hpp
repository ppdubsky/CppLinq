#pragma once

#include "Exceptions/FinishedEnumeratorException.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TContainer, typename TIterator = typename TContainer::const_iterator>
    struct OrderEnumerator final
    {
        using ValueType = typename TContainer::value_type;

        OrderEnumerator(const TContainer& container);

        auto GetCurrent() -> const ValueType&;
        auto IsFinished() -> bool;
        void MoveNext();

    private:
        void SortContainer();

        TIterator begin;
        TContainer container;
        TIterator end;
    };
}