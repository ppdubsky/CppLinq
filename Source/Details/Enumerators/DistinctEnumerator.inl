#pragma once

#include "Details/Enumerators/DistinctEnumerator.hpp"

#include <algorithm>

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TKeySelector, typename TKeyComparer>
    DistinctEnumerator<TEnumerator, TKeySelector, TKeyComparer>::DistinctEnumerator(const TEnumerator enumerator, const TKeySelector keySelector, const TKeyComparer keyComparer) :
        Base(enumerator),
        container(bucketCount, HasherType(), keyComparer),
        keySelector(keySelector)
    {
    }

    template <typename TEnumerator, typename TKeySelector, typename TKeyComparer>
    void DistinctEnumerator<TEnumerator, TKeySelector, TKeyComparer>::EnsureEnumeratorIsReady()
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

    template <typename TEnumerator, typename TKeySelector, typename TKeyComparer>
    auto DistinctEnumerator<TEnumerator, TKeySelector, TKeyComparer>::GetCurrent() -> Base::ValueType
    {
        EnsureEnumeratorIsReady();

        return Base::GetCurrent();
    }

    template <typename TEnumerator, typename TKeySelector, typename TKeyComparer>
    void DistinctEnumerator<TEnumerator, TKeySelector, TKeyComparer>::MoveNext()
    {
        Base::MoveNext();

        isReady = false;

        EnsureEnumeratorIsReady();
    }
}