#pragma once

#include "Details/Enumerators/UnionEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TUnionEnumerator, typename TSelector, typename TComparer>
    UnionEnumerator<TEnumerator, TUnionEnumerator, TSelector, TComparer>::UnionEnumerator(const TEnumerator enumerator, const TUnionEnumerator unionEnumerator, const TSelector selector, const TComparer comparer) :
        Base(enumerator),
        container(bucketCount, HasherType(), comparer),
        selector(selector),
        unionEnumerator(unionEnumerator)
    {
    }

    template <typename TEnumerator, typename TUnionEnumerator, typename TSelector, typename TComparer>
    void UnionEnumerator<TEnumerator, TUnionEnumerator, TSelector, TComparer>::EnsureEnumeratorIsReady()
    {
        if (!isReady)
        {
            auto isFound = false;

            while (Base::HasCurrent())
            {
                const KeyType currentKey = selector(Base::GetCurrent());

                const auto result = container.insert(currentKey);
                if (result.second)
                {
                    isFound = true;
                    break;
                }

                Base::MoveNext();
            }

            if (!isFound)
            {
                while (unionEnumerator.HasCurrent())
                {
                    const KeyType currentKey = selector(unionEnumerator.GetCurrent());

                    const auto result = container.insert(currentKey);
                    if (result.second)
                    {
                        isFound = true;
                        break;
                    }

                    unionEnumerator.MoveNext();
                }
            }

            isReady = true;
        }
    }

    template <typename TEnumerator, typename TUnionEnumerator, typename TSelector, typename TComparer>
    auto UnionEnumerator<TEnumerator, TUnionEnumerator, TSelector, TComparer>::GetCurrent() -> Base::ValueType
    {
        EnsureEnumeratorIsReady();

        return Base::HasCurrent() ? Base::GetCurrent() : unionEnumerator.GetCurrent();
    }

    template <typename TEnumerator, typename TUnionEnumerator, typename TSelector, typename TComparer>
    auto UnionEnumerator<TEnumerator, TUnionEnumerator, TSelector, TComparer>::HasCurrent() -> bool
    {
        EnsureEnumeratorIsReady();

        return Base::HasCurrent() || unionEnumerator.HasCurrent();
    }

    template <typename TEnumerator, typename TUnionEnumerator, typename TSelector, typename TComparer>
    void UnionEnumerator<TEnumerator, TUnionEnumerator, TSelector, TComparer>::MoveNext()
    {
        if (Base::HasCurrent())
        {
            Base::MoveNext();
        }
        else
        {
            unionEnumerator.MoveNext();
        }

        isReady = false;

        EnsureEnumeratorIsReady();
    }
}