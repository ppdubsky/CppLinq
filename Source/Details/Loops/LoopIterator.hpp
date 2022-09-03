#pragma once

#include "Details/Loops/LoopIteratorSentinel.hpp"

namespace CppLinq::Details::Loops
{
    template <typename TEnumerator>
    struct LoopIterator final
    {
        using ValueType = typename TEnumerator::ValueType;

        LoopIterator(const TEnumerator enumerator);

        auto operator++() -> LoopIterator&;
        auto operator*() -> ValueType;
        auto operator==(const LoopIteratorSentinel right) -> bool;
        auto operator!=(const LoopIteratorSentinel right) -> bool;

    private:
        TEnumerator enumerator;
    };
}