#pragma once

#include "Details/Enumerators/TakeEnumerator.hpp"

#include "Exceptions/FinishedEnumeratorException.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    TakeEnumerator<TEnumerator>::TakeEnumerator(const TEnumerator enumerator, const std::uint32_t count) :
        Base(enumerator),
        count(count)
    {
    }

    template <typename TEnumerator>
    auto TakeEnumerator<TEnumerator>::GetCurrent() -> Base::ValueType
    {
        if (IsFinished())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        return Base::GetCurrent();
    }

    template <typename TEnumerator>
    auto TakeEnumerator<TEnumerator>::IsFinished() -> bool
    {
        return count == 0U || Base::IsFinished();
    }

    template <typename TEnumerator>
    void TakeEnumerator<TEnumerator>::MoveNext()
    {
        if (count == 0U)
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        Base::MoveNext();

        --count;
    }
}