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
        if (!HasCurrent())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        return Base::GetCurrent();
    }

    template <typename TEnumerator>
    auto TakeEnumerator<TEnumerator>::HasCurrent() -> bool
    {
        return Base::HasCurrent() && count > 0U;
    }

    template <typename TEnumerator>
    void TakeEnumerator<TEnumerator>::MoveNext()
    {
        if (!HasCurrent())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        Base::MoveNext();

        --count;
    }
}