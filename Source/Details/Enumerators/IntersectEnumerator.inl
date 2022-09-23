#pragma once

#include "Details/Enumerators/IntersectEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TIntersectEnumerator, typename TKeySelector, typename TKeyComparer>
    IntersectEnumerator<TEnumerator, TIntersectEnumerator, TKeySelector, TKeyComparer>::IntersectEnumerator(const TEnumerator enumerator, const TIntersectEnumerator intersectEnumerator, const TKeySelector keySelector, const TKeyComparer keyComparer) :
        Base(enumerator),
        container(bucketCount, HasherType(), keyComparer),
        intersectEnumerator(intersectEnumerator),
        keySelector(keySelector)
    {
    }

    template <typename TEnumerator, typename TIntersectEnumerator, typename TKeySelector, typename TKeyComparer>
    void IntersectEnumerator<TEnumerator, TIntersectEnumerator, TKeySelector, TKeyComparer>::EnsureContainerIsReady()
    {
        if (!isContainerReady)
        {
            while (intersectEnumerator.HasCurrent())
            {
                container.insert(intersectEnumerator.GetCurrent());

                intersectEnumerator.MoveNext();
            }

            isContainerReady = true;
        }
    }

    template <typename TEnumerator, typename TIntersectEnumerator, typename TKeySelector, typename TKeyComparer>
    void IntersectEnumerator<TEnumerator, TIntersectEnumerator, TKeySelector, TKeyComparer>::EnsureEnumeratorIsReady()
    {
        if (!isReady)
        {
            EnsureContainerIsReady();

            while (Base::HasCurrent())
            {
                const KeyType currentKey = keySelector(Base::GetCurrent());

                const auto result = container.insert(currentKey);
                if (!result.second)
                {
                    break;
                }

                Base::MoveNext();
            }

            isReady = true;
        }
    }

    template <typename TEnumerator, typename TIntersectEnumerator, typename TKeySelector, typename TKeyComparer>
    auto IntersectEnumerator<TEnumerator, TIntersectEnumerator, TKeySelector, TKeyComparer>::GetCurrent() -> Base::ValueType
    {
        EnsureEnumeratorIsReady();

        return Base::GetCurrent();
    }

    template <typename TEnumerator, typename TIntersectEnumerator, typename TKeySelector, typename TKeyComparer>
    auto IntersectEnumerator<TEnumerator, TIntersectEnumerator, TKeySelector, TKeyComparer>::HasCurrent() -> bool
    {
        EnsureEnumeratorIsReady();

        return Base::HasCurrent();
    }

    template <typename TEnumerator, typename TIntersectEnumerator, typename TKeySelector, typename TKeyComparer>
    void IntersectEnumerator<TEnumerator, TIntersectEnumerator, TKeySelector, TKeyComparer>::MoveNext()
    {
        Base::MoveNext();

        isReady = false;

        EnsureEnumeratorIsReady();
    }
}