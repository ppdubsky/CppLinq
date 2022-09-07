#pragma once

#include "Details/Enumerators/ConcatenationEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TNextEnumerator>
    ConcatenationEnumerator<TEnumerator, TNextEnumerator>::ConcatenationEnumerator(const TEnumerator enumerator, const Query<TNextEnumerator>& nextQuery) :
        Base(enumerator),
        nextQuery(nextQuery)
    {
    }

    template <typename TEnumerator, typename TNextEnumerator>
    auto ConcatenationEnumerator<TEnumerator, TNextEnumerator>::GetCurrent() -> Base::ValueType
    {
        return Base::HasCurrent() ? Base::GetCurrent() : nextQuery.GetEnumerator().GetCurrent();
    }

    template <typename TEnumerator, typename TNextEnumerator>
    auto ConcatenationEnumerator<TEnumerator, TNextEnumerator>::HasCurrent() -> bool
    {
        return Base::HasCurrent() || nextQuery.GetEnumerator().HasCurrent();
    }

    template <typename TEnumerator, typename TNextEnumerator>
    void ConcatenationEnumerator<TEnumerator, TNextEnumerator>::MoveNext()
    {
        if (Base::HasCurrent())
        {
            Base::MoveNext();
        }
        else
        {
            nextQuery.GetEnumerator().MoveNext();
        }
    }
}