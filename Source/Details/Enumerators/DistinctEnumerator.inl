#pragma once

#include "Details/Enumerators/DistinctEnumerator.hpp"

#include <algorithm>

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TSelector, typename TComparer>
    DistinctEnumerator<TEnumerator, TSelector, TComparer>::DistinctEnumerator(const TEnumerator enumerator, const TSelector selector, const TComparer comparer) :
        Base(enumerator),
        comparer(comparer),
        selector(selector)
    {
    }

    template <typename TEnumerator, typename TSelector, typename TComparer>
    void DistinctEnumerator<TEnumerator, TSelector, TComparer>::EnsureEnumeratorIsReady()
    {
        if (!isReady)
        {
            while (Base::HasCurrent())
            {
                const KeyType currentKey = selector(Base::GetCurrent());

                const auto keyIterator = std::find_if(
                    keys.cbegin(),
                    keys.cend(),
                    [this, &currentKey](const KeyType& key)
                    {
                        return comparer.operator()(key, currentKey);
                    }
                );
                if (keyIterator == keys.cend())
                {
                    keys.push_back(currentKey);
                    break;
                }

                Base::MoveNext();
            }

            isReady = true;
        }
    }

    template <typename TEnumerator, typename TSelector, typename TComparer>
    auto DistinctEnumerator<TEnumerator, TSelector, TComparer>::GetCurrent() -> Base::ValueType
    {
        EnsureEnumeratorIsReady();

        return Base::GetCurrent();
    }

    template <typename TEnumerator, typename TSelector, typename TComparer>
    void DistinctEnumerator<TEnumerator, TSelector, TComparer>::MoveNext()
    {
        Base::MoveNext();

        isReady = false;

        EnsureEnumeratorIsReady();
    }
}