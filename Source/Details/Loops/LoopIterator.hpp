#pragma once

#include "Details/Loops/LoopIteratorSentinel.hpp"

namespace CppLinq::Details::Loops
{
    template <typename TEnumerator>
    struct LoopIterator final
    {
        using ValueType = typename TEnumerator::ValueType;

        LoopIterator(const TEnumerator enumerator) :
            enumerator(enumerator)
        {
        }

        auto operator++() -> LoopIterator&
        {
            enumerator.MoveNext();

            return *this;
        }

        auto operator*() -> ValueType
        {
            return enumerator.GetCurrent();
        }

        auto operator==(const LoopIteratorSentinel /*right*/) -> bool
        {
            return enumerator.IsFinished();
        }

        auto operator!=(const LoopIteratorSentinel right) -> bool
        {
            return !operator==(right);
        }

    private:
        TEnumerator enumerator;
    };
}