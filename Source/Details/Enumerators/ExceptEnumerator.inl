#pragma once

#include "Details/Enumerators/ExceptEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TExceptEnumerator, typename TKeySelector, typename TComparer>
    ExceptEnumerator<TEnumerator, TExceptEnumerator, TKeySelector, TComparer>::ExceptEnumerator(const TEnumerator enumerator, const TExceptEnumerator exceptEnumerator, const TKeySelector keySelector, const TComparer comparer) :
        Base(enumerator),
        container(bucketCount, HasherType(), comparer),
        exceptEnumerator(exceptEnumerator),
        keySelector(keySelector)
    {
    }

    template <typename TEnumerator, typename TExceptEnumerator, typename TKeySelector, typename TComparer>
    void ExceptEnumerator<TEnumerator, TExceptEnumerator, TKeySelector, TComparer>::EnsureContainerIsReady()
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

    template <typename TEnumerator, typename TExceptEnumerator, typename TKeySelector, typename TComparer>
    void ExceptEnumerator<TEnumerator, TExceptEnumerator, TKeySelector, TComparer>::EnsureEnumeratorIsReady()
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

    template <typename TEnumerator, typename TExceptEnumerator, typename TKeySelector, typename TComparer>
    auto ExceptEnumerator<TEnumerator, TExceptEnumerator, TKeySelector, TComparer>::GetCurrent() -> Base::ValueType
    {
        EnsureEnumeratorIsReady();

        return Base::GetCurrent();
    }

    template <typename TEnumerator, typename TExceptEnumerator, typename TKeySelector, typename TComparer>
    auto ExceptEnumerator<TEnumerator, TExceptEnumerator, TKeySelector, TComparer>::HasCurrent() -> bool
    {
        EnsureEnumeratorIsReady();

        return Base::HasCurrent();
    }

    template <typename TEnumerator, typename TExceptEnumerator, typename TKeySelector, typename TComparer>
    void ExceptEnumerator<TEnumerator, TExceptEnumerator, TKeySelector, TComparer>::MoveNext()
    {
        Base::MoveNext();

        isReady = false;

        EnsureEnumeratorIsReady();
    }
}