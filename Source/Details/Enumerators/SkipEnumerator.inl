#pragma once

#include "Details/Enumerators/SkipEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    SkipEnumerator<TEnumerator>::SkipEnumerator(const TEnumerator enumerator, const std::uint32_t count) :
        Base(enumerator),
        count(count)
    {
    }

    template <typename TEnumerator>
    void SkipEnumerator<TEnumerator>::EnsureEnumeratorIsReady()
    {
        if (!isReady)
        {
            while (count > 0U && !Base::IsFinished())
            {
                Base::MoveNext();

                --count;
            }

            isReady = true;
        }
    }

    template <typename TEnumerator>
    auto SkipEnumerator<TEnumerator>::GetCurrent() -> Base::ValueType
    {
        EnsureEnumeratorIsReady();

        return Base::GetCurrent();
    }

    template <typename TEnumerator>
    auto SkipEnumerator<TEnumerator>::IsFinished() -> bool
    {
        EnsureEnumeratorIsReady();

        return Base::IsFinished();
    }

    template <typename TEnumerator>
    void SkipEnumerator<TEnumerator>::MoveNext()
    {
        EnsureEnumeratorIsReady();

        Base::MoveNext();
    }
}