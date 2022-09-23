#pragma once

#include "Details/Enumerators/UnionEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TUnionEnumerator, typename TKeySelector, typename TKeyComparer>
    UnionEnumerator<TEnumerator, TUnionEnumerator, TKeySelector, TKeyComparer>::UnionEnumerator(const TEnumerator enumerator, const TUnionEnumerator unionEnumerator, const TKeySelector keySelector, const TKeyComparer keyComparer) :
        Base(enumerator),
        container(bucketCount, HasherType(), keyComparer),
        keySelector(keySelector),
        unionEnumerator(unionEnumerator)
    {
    }

    template <typename TEnumerator, typename TUnionEnumerator, typename TKeySelector, typename TKeyComparer>
    void UnionEnumerator<TEnumerator, TUnionEnumerator, TKeySelector, TKeyComparer>::EnsureEnumeratorIsReady()
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

    template <typename TEnumerator, typename TUnionEnumerator, typename TKeySelector, typename TKeyComparer>
    auto UnionEnumerator<TEnumerator, TUnionEnumerator, TKeySelector, TKeyComparer>::GetCurrent() -> Base::ValueType
    {
        EnsureEnumeratorIsReady();

        return Base::HasCurrent() ? Base::GetCurrent() : unionEnumerator.GetCurrent();
    }

    template <typename TEnumerator, typename TUnionEnumerator, typename TKeySelector, typename TKeyComparer>
    auto UnionEnumerator<TEnumerator, TUnionEnumerator, TKeySelector, TKeyComparer>::HasCurrent() -> bool
    {
        EnsureEnumeratorIsReady();

        return Base::HasCurrent() || unionEnumerator.HasCurrent();
    }

    template <typename TEnumerator, typename TUnionEnumerator, typename TKeySelector, typename TKeyComparer>
    void UnionEnumerator<TEnumerator, TUnionEnumerator, TKeySelector, TKeyComparer>::MoveNext()
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