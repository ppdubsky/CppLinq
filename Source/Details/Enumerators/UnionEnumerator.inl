#pragma once

#include "Details/Enumerators/UnionEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TUnionEnumerator, typename TKeySelector, typename TComparer>
    UnionEnumerator<TEnumerator, TUnionEnumerator, TKeySelector, TComparer>::UnionEnumerator(const TEnumerator enumerator, const TUnionEnumerator unionEnumerator, const TKeySelector keySelector, const TComparer comparer) :
        Base(enumerator),
        container(bucketCount, HasherType(), comparer),
        keySelector(keySelector),
        unionEnumerator(unionEnumerator)
    {
    }

    template <typename TEnumerator, typename TUnionEnumerator, typename TKeySelector, typename TComparer>
    void UnionEnumerator<TEnumerator, TUnionEnumerator, TKeySelector, TComparer>::EnsureEnumeratorIsReady()
    {
        if (!isReady)
        {
            auto isFound = false;

            while (Base::HasCurrent())
            {
                const KeyType currentKey = keySelector(Base::GetCurrent());

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
                    const KeyType currentKey = keySelector(unionEnumerator.GetCurrent());

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

    template <typename TEnumerator, typename TUnionEnumerator, typename TKeySelector, typename TComparer>
    auto UnionEnumerator<TEnumerator, TUnionEnumerator, TKeySelector, TComparer>::GetCurrent() -> Base::ValueType
    {
        EnsureEnumeratorIsReady();

        return Base::HasCurrent() ? Base::GetCurrent() : unionEnumerator.GetCurrent();
    }

    template <typename TEnumerator, typename TUnionEnumerator, typename TKeySelector, typename TComparer>
    auto UnionEnumerator<TEnumerator, TUnionEnumerator, TKeySelector, TComparer>::HasCurrent() -> bool
    {
        EnsureEnumeratorIsReady();

        return Base::HasCurrent() || unionEnumerator.HasCurrent();
    }

    template <typename TEnumerator, typename TUnionEnumerator, typename TKeySelector, typename TComparer>
    void UnionEnumerator<TEnumerator, TUnionEnumerator, TKeySelector, TComparer>::MoveNext()
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