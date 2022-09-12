#pragma once

#include "Details/Enumerators/DistinctEnumerator.hpp"

#include <algorithm>

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TSelector, typename TComparer>
    DistinctEnumerator<TEnumerator, TSelector, TComparer>::DistinctEnumerator(const TEnumerator enumerator, const TSelector selector, const TComparer comparer) :
        Base(enumerator),
        container(bucketCount, HasherType(), comparer),
        selector(selector)
    {
    }

    template <typename TEnumerator, typename TSelector, typename TComparer>
    void DistinctEnumerator<TEnumerator, TSelector, TComparer>::EnsureEnumeratorIsReady()
    {
        if (!isReady)
        {
            while (Base::HasCurrent())
            {
                const KeyType currentKey = selector(Base::GetCurrent());

                const auto result = container.insert(currentKey);
                if (result.second)
                {
                    break;
                }

                Base::MoveNext();
            }

            isReady = true;
        }
    }

    template <typename TEnumerator, typename TSelector, typename TComparer>
    auto DistinctEnumerator<TEnumerator, TSelector, TComparer>::GetCurrent() -> Base::ValueType
    {
        EnsureEnumeratorIsReady();

        return Base::GetCurrent();
    }

    template <typename TEnumerator, typename TSelector, typename TComparer>
    void DistinctEnumerator<TEnumerator, TSelector, TComparer>::MoveNext()
    {
        Base::MoveNext();

        isReady = false;

        EnsureEnumeratorIsReady();
    }
}