#pragma once

#include "Details/Enumerators/InnerJoinEnumerator.hpp"

#include "Exceptions/FinishedEnumeratorException.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TOtherEnumerator, typename TSelector, typename TOtherSelector, typename TResultSelector, typename TComparer>
    InnerJoinEnumerator<TEnumerator, TOtherEnumerator, TSelector, TOtherSelector, TResultSelector, TComparer>::InnerJoinEnumerator(const TEnumerator enumerator, const TOtherEnumerator otherEnumerator, const TSelector selector, const TOtherSelector otherSelector, const TResultSelector resultSelector, const TComparer comparer) :
        Base(enumerator),
        container(bucketCount, HasherType(), comparer),
        otherEnumerator(otherEnumerator),
        otherSelector(otherSelector),
        resultSelector(resultSelector),
        selector(selector)
    {
    }

    template <typename TEnumerator, typename TOtherEnumerator, typename TSelector, typename TOtherSelector, typename TResultSelector, typename TComparer>
    void InnerJoinEnumerator<TEnumerator, TOtherEnumerator, TSelector, TOtherSelector, TResultSelector, TComparer>::EnsureContainerIsReady()
    {
        if (!isContainerReady)
        {
            while (otherEnumerator.HasCurrent())
            {
                const auto current = otherEnumerator.GetCurrent();
                const auto key = otherSelector(current);

                container.insert({ key, current });

                otherEnumerator.MoveNext();
            }

            isContainerReady = true;
        }
    }

    template <typename TEnumerator, typename TOtherEnumerator, typename TSelector, typename TOtherSelector, typename TResultSelector, typename TComparer>
    void InnerJoinEnumerator<TEnumerator, TOtherEnumerator, TSelector, TOtherSelector, TResultSelector, TComparer>::EnsureEnumeratorIsReady()
    {
        if (!isReady)
        {
            EnsureContainerIsReady();

            QueueType emptyQueue;
            queue.swap(emptyQueue);

            while (queue.empty() && Base::HasCurrent())
            {
                const auto current = Base::GetCurrent();
                const auto key = selector(current);

                const auto range = container.equal_range(key);
                for (auto iterator = range.first; iterator != range.second; ++iterator)
                {
                    queue.push(resultSelector(current, iterator->second));
                }

                Base::MoveNext();
            }

            isReady = true;
        }
    }

    template <typename TEnumerator, typename TOtherEnumerator, typename TSelector, typename TOtherSelector, typename TResultSelector, typename TComparer>
    auto InnerJoinEnumerator<TEnumerator, TOtherEnumerator, TSelector, TOtherSelector, TResultSelector, TComparer>::GetCurrent() -> ValueType
    {
        EnsureEnumeratorIsReady();

        if (queue.empty())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        return queue.front();;
    }

    template <typename TEnumerator, typename TOtherEnumerator, typename TSelector, typename TOtherSelector, typename TResultSelector, typename TComparer>
    auto InnerJoinEnumerator<TEnumerator, TOtherEnumerator, TSelector, TOtherSelector, TResultSelector, TComparer>::HasCurrent() -> bool
    {
        EnsureEnumeratorIsReady();

        return !queue.empty();
    }

    template <typename TEnumerator, typename TOtherEnumerator, typename TSelector, typename TOtherSelector, typename TResultSelector, typename TComparer>
    void InnerJoinEnumerator<TEnumerator, TOtherEnumerator, TSelector, TOtherSelector, TResultSelector, TComparer>::MoveNext()
    {
        if (queue.empty())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        queue.pop();

        if (queue.empty())
        {
            isReady = false;

            EnsureEnumeratorIsReady();
        }
    }
}