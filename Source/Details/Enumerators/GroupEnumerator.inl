#pragma once

#include "Details/Enumerators/GroupEnumerator.hpp"

#include <algorithm>

#include "Exceptions/FinishedEnumeratorException.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TKeySelector, typename TElementSelector, typename TResultSelector, typename TKeyComparer>
    GroupEnumerator<TEnumerator, TKeySelector, TElementSelector, TResultSelector, TKeyComparer>::GroupEnumerator(const TEnumerator enumerator, const TKeySelector keySelector, const TElementSelector elementSelector, const TResultSelector resultSelector, const TKeyComparer keyComparer) :
        Base(enumerator),
        elementSelector(elementSelector),
        groupContainer(bucketCount, HasherType(), keyComparer),
        keySelector(keySelector),
        resultSelector(resultSelector)
    {
    }

    template <typename TEnumerator, typename TKeySelector, typename TElementSelector, typename TResultSelector, typename TKeyComparer>
    void GroupEnumerator<TEnumerator, TKeySelector, TElementSelector, TResultSelector, TKeyComparer>::EnsureEnumeratorIsReady()
    {
        if (!isReady)
        {
            while (Base::HasCurrent())
            {
                const auto current = Base::GetCurrent();
                const auto key = keySelector(current);

                const auto keyIterator = std::find_if(
                    keyContainer.cbegin(),
                    keyContainer.cend(),
                    [this, &key](const auto value){ return groupContainer.key_eq()(value, key); }
                );
                if (keyIterator == keyContainer.cend())
                {
                    keyContainer.push_back(key);
                }

                groupContainer.insert({ key, current });

                Base::MoveNext();
            }

            isReady = true;
        }
    }

    template <typename TEnumerator, typename TKeySelector, typename TElementSelector, typename TResultSelector, typename TKeyComparer>
    auto GroupEnumerator<TEnumerator, TKeySelector, TElementSelector, TResultSelector, TKeyComparer>::GetCurrent() -> ValueType
    {
        EnsureEnumeratorIsReady();

        if (keyContainer.empty())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        const auto key = keyContainer.front();

        ElementContainer elementContainer;
        
        const auto range = groupContainer.equal_range(key);
        for (auto iterator = range.first; iterator != range.second; ++iterator)
        {
            elementContainer.push_back(elementSelector(iterator->second));
        }

        return resultSelector(key, elementContainer);
    }

    template <typename TEnumerator, typename TKeySelector, typename TElementSelector, typename TResultSelector, typename TKeyComparer>
    auto GroupEnumerator<TEnumerator, TKeySelector, TElementSelector, TResultSelector, TKeyComparer>::HasCurrent() -> bool
    {
        EnsureEnumeratorIsReady();

        return !keyContainer.empty();
    }

    template <typename TEnumerator, typename TKeySelector, typename TElementSelector, typename TResultSelector, typename TKeyComparer>
    void GroupEnumerator<TEnumerator, TKeySelector, TElementSelector, TResultSelector, TKeyComparer>::MoveNext()
    {
        EnsureEnumeratorIsReady();

        if (keyContainer.empty())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        keyContainer.erase(keyContainer.begin());
    }
}