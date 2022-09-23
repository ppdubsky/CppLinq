#pragma once

#include "Details/Enumerators/DistinctEnumerator.hpp"

#include <algorithm>

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TKeySelector, typename TComparer>
    DistinctEnumerator<TEnumerator, TKeySelector, TComparer>::DistinctEnumerator(const TEnumerator enumerator, const TKeySelector keySelector, const TComparer comparer) :
        Base(enumerator),
        container(bucketCount, HasherType(), comparer),
        keySelector(keySelector)
    {
    }

    template <typename TEnumerator, typename TKeySelector, typename TComparer>
    void DistinctEnumerator<TEnumerator, TKeySelector, TComparer>::EnsureEnumeratorIsReady()
    {
        if (!isReady)
        {
            while (Base::HasCurrent())
            {
                const KeyType currentKey = keySelector(Base::GetCurrent());

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

    template <typename TEnumerator, typename TKeySelector, typename TComparer>
    auto DistinctEnumerator<TEnumerator, TKeySelector, TComparer>::GetCurrent() -> Base::ValueType
    {
        EnsureEnumeratorIsReady();

        return Base::GetCurrent();
    }

    template <typename TEnumerator, typename TKeySelector, typename TComparer>
    void DistinctEnumerator<TEnumerator, TKeySelector, TComparer>::MoveNext()
    {
        Base::MoveNext();

        isReady = false;

        EnsureEnumeratorIsReady();
    }
}