#pragma once

#include "Exceptions/FinishedEnumeratorException.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TContainer>
    struct OrderEnumerator final
    {
        using IteratorType = typename TContainer::const_iterator;
        using ValueType = typename TContainer::value_type;

        OrderEnumerator(const TContainer& container);

        auto GetCurrent() -> const ValueType&;
        auto IsFinished() -> bool;
        void MoveNext();

    private:
        void SortContainer();

        IteratorType begin;
        TContainer container;
        IteratorType end;
    };
}