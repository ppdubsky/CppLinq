#pragma once

#include "Details/Enumerators/ExceptEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TExceptEnumerator, typename TSelector, typename TComparer>
    ExceptEnumerator<TEnumerator, TExceptEnumerator, TSelector, TComparer>::ExceptEnumerator(const TEnumerator enumerator, const TExceptEnumerator exceptEnumerator, const TSelector selector, const TComparer comparer) :
        Base(enumerator),
        container(bucketCount, HasherType(), comparer),
        exceptEnumerator(exceptEnumerator),
        selector(selector)
    {
    }

    template <typename TEnumerator, typename TExceptEnumerator, typename TSelector, typename TComparer>
    void ExceptEnumerator<TEnumerator, TExceptEnumerator, TSelector, TComparer>::EnsureContainerIsReady()
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

    template <typename TEnumerator, typename TExceptEnumerator, typename TSelector, typename TComparer>
    void ExceptEnumerator<TEnumerator, TExceptEnumerator, TSelector, TComparer>::EnsureEnumeratorIsReady()
    {
        if (!isReady)
        {
            EnsureContainerIsReady();

            while (Base::HasCurrent())
            {
                const KeyType currentKey = selector(Base::GetCurrent());

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

    template <typename TEnumerator, typename TExceptEnumerator, typename TSelector, typename TComparer>
    auto ExceptEnumerator<TEnumerator, TExceptEnumerator, TSelector, TComparer>::GetCurrent() -> Base::ValueType
    {
        EnsureEnumeratorIsReady();

        return Base::GetCurrent();
    }

    template <typename TEnumerator, typename TExceptEnumerator, typename TSelector, typename TComparer>
    auto ExceptEnumerator<TEnumerator, TExceptEnumerator, TSelector, TComparer>::HasCurrent() -> bool
    {
        EnsureEnumeratorIsReady();

        return Base::HasCurrent();
    }

    template <typename TEnumerator, typename TExceptEnumerator, typename TSelector, typename TComparer>
    void ExceptEnumerator<TEnumerator, TExceptEnumerator, TSelector, TComparer>::MoveNext()
    {
        Base::MoveNext();

        isReady = false;

        EnsureEnumeratorIsReady();
    }
}