#pragma once

#include "Details/Enumerators/ExceptEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TFirstEnumerator, typename TSecondEnumerator, typename TKeySelector, typename TKeyComparer>
    ExceptEnumerator<TFirstEnumerator, TSecondEnumerator, TKeySelector, TKeyComparer>::ExceptEnumerator(const TFirstEnumerator firstEnumerator, const TSecondEnumerator secondEnumerator, const TKeySelector keySelector, const TKeyComparer keyComparer) :
        Base(firstEnumerator),
        container(bucketCount, HasherType(), keyComparer),
        keySelector(keySelector),
        secondEnumerator(secondEnumerator)
    {
    }

    template <typename TFirstEnumerator, typename TSecondEnumerator, typename TKeySelector, typename TKeyComparer>
    void ExceptEnumerator<TFirstEnumerator, TSecondEnumerator, TKeySelector, TKeyComparer>::EnsureContainerIsReady()
    {
        if (!isContainerReady)
        {
            while (secondEnumerator.HasCurrent())
            {
                container.insert(secondEnumerator.GetCurrent());

                secondEnumerator.MoveNext();
            }

            isContainerReady = true;
        }
    }

    template <typename TFirstEnumerator, typename TSecondEnumerator, typename TKeySelector, typename TKeyComparer>
    void ExceptEnumerator<TFirstEnumerator, TSecondEnumerator, TKeySelector, TKeyComparer>::EnsureEnumeratorIsReady()
    {
        if (!isReady)
        {
            EnsureContainerIsReady();

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

    template <typename TFirstEnumerator, typename TSecondEnumerator, typename TKeySelector, typename TKeyComparer>
    auto ExceptEnumerator<TFirstEnumerator, TSecondEnumerator, TKeySelector, TKeyComparer>::GetCurrent() -> Base::ValueType
    {
        EnsureEnumeratorIsReady();

        return Base::GetCurrent();
    }

    template <typename TFirstEnumerator, typename TSecondEnumerator, typename TKeySelector, typename TKeyComparer>
    auto ExceptEnumerator<TFirstEnumerator, TSecondEnumerator, TKeySelector, TKeyComparer>::HasCurrent() -> bool
    {
        EnsureEnumeratorIsReady();

        return Base::HasCurrent();
    }

    template <typename TFirstEnumerator, typename TSecondEnumerator, typename TKeySelector, typename TKeyComparer>
    void ExceptEnumerator<TFirstEnumerator, TSecondEnumerator, TKeySelector, TKeyComparer>::MoveNext()
    {
        Base::MoveNext();

        isReady = false;

        EnsureEnumeratorIsReady();
    }
}