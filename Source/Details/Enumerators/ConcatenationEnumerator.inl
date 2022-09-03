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
        return Base::IsFinished() ? nextQuery.GetEnumerator().GetCurrent() : Base::GetCurrent();
    }

    template <typename TEnumerator, typename TNextEnumerator>
    auto ConcatenationEnumerator<TEnumerator, TNextEnumerator>::IsFinished() -> bool
    {
        return Base::IsFinished() && nextQuery.GetEnumerator().IsFinished();
    }

    template <typename TEnumerator, typename TNextEnumerator>
    void ConcatenationEnumerator<TEnumerator, TNextEnumerator>::MoveNext()
    {
        if (Base::IsFinished())
        {
            nextQuery.GetEnumerator().MoveNext();
        }
        else
        {
            Base::MoveNext();
        }
    }
}