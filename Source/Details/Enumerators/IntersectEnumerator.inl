#pragma once

#include "Details/Enumerators/IntersectEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TIntersectEnumerator, typename TKeySelector, typename TComparer>
    IntersectEnumerator<TEnumerator, TIntersectEnumerator, TKeySelector, TComparer>::IntersectEnumerator(const TEnumerator enumerator, const TIntersectEnumerator intersectEnumerator, const TKeySelector keySelector, const TComparer comparer) :
        Base(enumerator),
        container(bucketCount, HasherType(), comparer),
        intersectEnumerator(intersectEnumerator),
        keySelector(keySelector)
    {
    }

    template <typename TEnumerator, typename TIntersectEnumerator, typename TKeySelector, typename TComparer>
    void IntersectEnumerator<TEnumerator, TIntersectEnumerator, TKeySelector, TComparer>::EnsureContainerIsReady()
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

    template <typename TEnumerator, typename TIntersectEnumerator, typename TKeySelector, typename TComparer>
    void IntersectEnumerator<TEnumerator, TIntersectEnumerator, TKeySelector, TComparer>::EnsureEnumeratorIsReady()
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

    template <typename TEnumerator, typename TIntersectEnumerator, typename TKeySelector, typename TComparer>
    auto IntersectEnumerator<TEnumerator, TIntersectEnumerator, TKeySelector, TComparer>::GetCurrent() -> Base::ValueType
    {
        EnsureEnumeratorIsReady();

        return Base::GetCurrent();
    }

    template <typename TEnumerator, typename TIntersectEnumerator, typename TKeySelector, typename TComparer>
    auto IntersectEnumerator<TEnumerator, TIntersectEnumerator, TKeySelector, TComparer>::HasCurrent() -> bool
    {
        EnsureEnumeratorIsReady();

        return Base::HasCurrent();
    }

    template <typename TEnumerator, typename TIntersectEnumerator, typename TKeySelector, typename TComparer>
    void IntersectEnumerator<TEnumerator, TIntersectEnumerator, TKeySelector, TComparer>::MoveNext()
    {
        Base::MoveNext();

        isReady = false;

        EnsureEnumeratorIsReady();
    }
}