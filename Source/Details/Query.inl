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
    auto Query<TEnumerator>::GetEnumerator() const -> const TEnumerator&
    {
        return enumerator;
    }

    template <typename TEnumerator>
    auto begin(const Query<TEnumerator>& query) -> Loops::LoopIterator<TEnumerator>
    {
        return { query.GetEnumerator() };
    }

    template <typename TEnumerator>
    auto end(const Query<TEnumerator>& /*query*/) -> Loops::LoopIteratorSentinel
    {
        return {};
    }
}