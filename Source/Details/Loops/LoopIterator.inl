#pragma once

#include "Details/Loops/LoopIterator.hpp"

namespace CppLinq::Details::Loops
{
    template <typename TEnumerator>
    LoopIterator<TEnumerator>::LoopIterator(const TEnumerator enumerator) :
        enumerator(enumerator)
    {
    }

    template <typename TEnumerator>
    auto LoopIterator<TEnumerator>::operator++() -> LoopIterator&
    {
        enumerator.MoveNext();

        return *this;
    }

    template <typename TEnumerator>
    auto LoopIterator<TEnumerator>::operator*() -> ValueType
    {
        return enumerator.GetCurrent();
    }

    template <typename TEnumerator>
    auto LoopIterator<TEnumerator>::operator==(const LoopIteratorSentinel /*right*/) -> bool
    {
        return enumerator.IsFinished();
    }

    template <typename TEnumerator>
    auto LoopIterator<TEnumerator>::operator!=(const LoopIteratorSentinel right) -> bool
    {
        return !operator==(right);
    }
}