#pragma once

#include "Details/Enumerators/IntersectEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TIntersectEnumerator, typename TSelector, typename TComparer>
    IntersectEnumerator<TEnumerator, TIntersectEnumerator, TSelector, TComparer>::IntersectEnumerator(const TEnumerator enumerator, const TIntersectEnumerator intersectEnumerator, const TSelector selector, const TComparer comparer) :
        Base(enumerator),
        container(bucketCount, HasherType(), comparer),
        intersectEnumerator(intersectEnumerator),
        selector(selector)
    {
    }

    template <typename TEnumerator, typename TIntersectEnumerator, typename TSelector, typename TComparer>
    void IntersectEnumerator<TEnumerator, TIntersectEnumerator, TSelector, TComparer>::EnsureContainerIsReady()
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

    template <typename TEnumerator, typename TIntersectEnumerator, typename TSelector, typename TComparer>
    void IntersectEnumerator<TEnumerator, TIntersectEnumerator, TSelector, TComparer>::EnsureEnumeratorIsReady()
    {
        if (!isReady)
        {
            EnsureContainerIsReady();

            while (Base::HasCurrent())
            {
                const KeyType currentKey = selector(Base::GetCurrent());

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

    template <typename TEnumerator, typename TIntersectEnumerator, typename TSelector, typename TComparer>
    auto IntersectEnumerator<TEnumerator, TIntersectEnumerator, TSelector, TComparer>::GetCurrent() -> Base::ValueType
    {
        EnsureEnumeratorIsReady();

        return Base::GetCurrent();
    }

    template <typename TEnumerator, typename TIntersectEnumerator, typename TSelector, typename TComparer>
    auto IntersectEnumerator<TEnumerator, TIntersectEnumerator, TSelector, TComparer>::HasCurrent() -> bool
    {
        EnsureEnumeratorIsReady();

        return Base::HasCurrent();
    }

    template <typename TEnumerator, typename TIntersectEnumerator, typename TSelector, typename TComparer>
    void IntersectEnumerator<TEnumerator, TIntersectEnumerator, TSelector, TComparer>::MoveNext()
    {
        Base::MoveNext();

        isReady = false;

        EnsureEnumeratorIsReady();
    }
}