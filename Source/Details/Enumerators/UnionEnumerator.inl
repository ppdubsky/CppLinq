#pragma once

#include "Details/Enumerators/UnionEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TFirstEnumerator, typename TSecondEnumerator, typename TKeySelector, typename TKeyComparer>
    UnionEnumerator<TFirstEnumerator, TSecondEnumerator, TKeySelector, TKeyComparer>::UnionEnumerator(const TFirstEnumerator firstEnumerator, const TSecondEnumerator secondEnumerator, const TKeySelector keySelector, const TKeyComparer keyComparer) :
        Base(firstEnumerator),
        container(bucketCount, HasherType(), keyComparer),
        keySelector(keySelector),
        secondEnumerator(secondEnumerator)
    {
    }

    template <typename TFirstEnumerator, typename TSecondEnumerator, typename TKeySelector, typename TKeyComparer>
    void UnionEnumerator<TFirstEnumerator, TSecondEnumerator, TKeySelector, TKeyComparer>::EnsureEnumeratorIsReady()
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
                while (secondEnumerator.HasCurrent())
                {
                    const KeyType currentKey = keySelector(secondEnumerator.GetCurrent());

                    const auto result = container.insert(currentKey);
                    if (result.second)
                    {
                        isFound = true;
                        break;
                    }

                    secondEnumerator.MoveNext();
                }
            }

            isReady = true;
        }
    }

    template <typename TFirstEnumerator, typename TSecondEnumerator, typename TKeySelector, typename TKeyComparer>
    auto UnionEnumerator<TFirstEnumerator, TSecondEnumerator, TKeySelector, TKeyComparer>::GetCurrent() -> Base::ValueType
    {
        EnsureEnumeratorIsReady();

        return Base::HasCurrent() ? Base::GetCurrent() : secondEnumerator.GetCurrent();
    }

    template <typename TFirstEnumerator, typename TSecondEnumerator, typename TKeySelector, typename TKeyComparer>
    auto UnionEnumerator<TFirstEnumerator, TSecondEnumerator, TKeySelector, TKeyComparer>::HasCurrent() -> bool
    {
        EnsureEnumeratorIsReady();

        return Base::HasCurrent() || secondEnumerator.HasCurrent();
    }

    template <typename TFirstEnumerator, typename TSecondEnumerator, typename TKeySelector, typename TKeyComparer>
    void UnionEnumerator<TFirstEnumerator, TSecondEnumerator, TKeySelector, TKeyComparer>::MoveNext()
    {
        if (Base::HasCurrent())
        {
            Base::MoveNext();
        }
        else
        {
            secondEnumerator.MoveNext();
        }

        isReady = false;

        EnsureEnumeratorIsReady();
    }
}