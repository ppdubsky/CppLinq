#pragma once

#include "Details/Enumerators/ExceptEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TExceptEnumerator, typename TKeySelector, typename TKeyComparer>
    ExceptEnumerator<TEnumerator, TExceptEnumerator, TKeySelector, TKeyComparer>::ExceptEnumerator(const TEnumerator enumerator, const TExceptEnumerator exceptEnumerator, const TKeySelector keySelector, const TKeyComparer keyComparer) :
        Base(enumerator),
        container(bucketCount, HasherType(), keyComparer),
        exceptEnumerator(exceptEnumerator),
        keySelector(keySelector)
    {
    }

    template <typename TEnumerator, typename TExceptEnumerator, typename TKeySelector, typename TKeyComparer>
    void ExceptEnumerator<TEnumerator, TExceptEnumerator, TKeySelector, TKeyComparer>::EnsureContainerIsReady()
    {
        if (!isContainerReady)
        {
            while (exceptEnumerator.HasCurrent())
            {
                container.insert(exceptEnumerator.GetCurrent());

                exceptEnumerator.MoveNext();
            }

            isContainerReady = true;
        }
    }

    template <typename TEnumerator, typename TExceptEnumerator, typename TKeySelector, typename TKeyComparer>
    void ExceptEnumerator<TEnumerator, TExceptEnumerator, TKeySelector, TKeyComparer>::EnsureEnumeratorIsReady()
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

    template <typename TEnumerator, typename TExceptEnumerator, typename TKeySelector, typename TKeyComparer>
    auto ExceptEnumerator<TEnumerator, TExceptEnumerator, TKeySelector, TKeyComparer>::GetCurrent() -> Base::ValueType
    {
        EnsureEnumeratorIsReady();

        return Base::GetCurrent();
    }

    template <typename TEnumerator, typename TExceptEnumerator, typename TKeySelector, typename TKeyComparer>
    auto ExceptEnumerator<TEnumerator, TExceptEnumerator, TKeySelector, TKeyComparer>::HasCurrent() -> bool
    {
        EnsureEnumeratorIsReady();

        return Base::HasCurrent();
    }

    template <typename TEnumerator, typename TExceptEnumerator, typename TKeySelector, typename TKeyComparer>
    void ExceptEnumerator<TEnumerator, TExceptEnumerator, TKeySelector, TKeyComparer>::MoveNext()
    {
        Base::MoveNext();

        isReady = false;

        EnsureEnumeratorIsReady();
    }
}