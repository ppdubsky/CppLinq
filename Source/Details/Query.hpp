#pragma once

#include "Enumerators/SelectEnumerator.hpp"
#include "Enumerators/WhereEnumerator.hpp"
#include "Loops/LoopIterator.hpp"
#include "Loops/LoopIteratorSentinel.hpp"

namespace CppLinq::Details
{
    template <typename TEnumerator>
    struct Query final
    {
        Query(const TEnumerator enumerator) :
            enumerator(enumerator)
        {
        }

        auto begin() const -> Loops::LoopIterator<TEnumerator>
        {
            return { enumerator };
        }

        auto end() const -> Loops::LoopIteratorSentinel
        {
            return {};
        }

        template <typename TSelector>
        auto Select(const TSelector selector) -> Query<Enumerators::SelectEnumerator<TEnumerator, TSelector>>
        {
            return { { enumerator, selector } };
        }

        template <typename TPredicate>
        auto Where(const TPredicate predicate) -> Query<Enumerators::WhereEnumerator<TEnumerator, TPredicate>>
        {
            return { { enumerator, predicate } };
        }

    private:
        TEnumerator enumerator;
    };
}