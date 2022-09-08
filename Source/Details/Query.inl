#pragma once

#include "Details/Query.hpp"

#include "Details/Loops/LoopIterator.hpp"
#include "Details/Loops/LoopIteratorSentinel.hpp"

namespace CppLinq::Details
{
    template <typename TEnumerator>
    Query<TEnumerator>::Query(const TEnumerator enumerator) :
        enumerator(enumerator)
    {
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::begin() const -> Loops::LoopIterator<TEnumerator>
    {
        return { enumerator };
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::end() const -> Loops::LoopIteratorSentinel
    {
        return {};
    }

    template <typename TEnumerator>
    auto Query<TEnumerator>::GetEnumerator() const -> const TEnumerator&
    {
        return enumerator;
    }
}