#pragma once

#include "Details/Enumerators/LeftJoinEnumerator.hpp"

#include "Exceptions/FinishedEnumeratorException.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TOtherEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TKeyComparer>
    LeftJoinEnumerator<TEnumerator, TOtherEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TKeyComparer>::LeftJoinEnumerator(const TEnumerator enumerator, const TOtherEnumerator otherEnumerator, const TLeftKeySelector leftKeySelector, const TRightKeySelector rightKeySelector, const TResultSelector resultSelector, const TKeyComparer keyComparer) :
        Base(enumerator),
        container(bucketCount, HasherType(), keyComparer),
        leftKeySelector(leftKeySelector),
        otherEnumerator(otherEnumerator),
        resultSelector(resultSelector),
        rightKeySelector(rightKeySelector)
    {
    }

    template <typename TEnumerator, typename TOtherEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TKeyComparer>
    void LeftJoinEnumerator<TEnumerator, TOtherEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TKeyComparer>::EnsureContainerIsReady()
    {
        if (!isContainerReady)
        {
            while (otherEnumerator.HasCurrent())
            {
                const auto current = otherEnumerator.GetCurrent();
                const auto key = rightKeySelector(current);

                container.insert({ key, current });

                otherEnumerator.MoveNext();
            }

            isContainerReady = true;
        }
    }

    template <typename TEnumerator, typename TOtherEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TKeyComparer>
    void LeftJoinEnumerator<TEnumerator, TOtherEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TKeyComparer>::EnsureEnumeratorIsReady()
    {
        if (!isReady)
        {
            EnsureContainerIsReady();

            QueueType emptyQueue;
            queue.swap(emptyQueue);

            while (queue.empty() && Base::HasCurrent())
            {
                const auto current = Base::GetCurrent();
                const auto key = leftKeySelector(current);

                const auto range = container.equal_range(key);
                if (range.first == range.second)
                {
                    queue.push(resultSelector(current, std::nullopt));
                }
                else
                {
                    for (auto iterator = range.first; iterator != range.second; ++iterator)
                    {
                        queue.push(resultSelector(current, iterator->second));
                    }
                }

                Base::MoveNext();
            }

            isReady = true;
        }
    }

    template <typename TEnumerator, typename TOtherEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TKeyComparer>
    auto LeftJoinEnumerator<TEnumerator, TOtherEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TKeyComparer>::GetCurrent() -> ValueType
    {
        EnsureEnumeratorIsReady();

        if (queue.empty())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        return queue.front();
    }

    template <typename TEnumerator, typename TOtherEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TKeyComparer>
    auto LeftJoinEnumerator<TEnumerator, TOtherEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TKeyComparer>::HasCurrent() -> bool
    {
        EnsureEnumeratorIsReady();

        return !queue.empty();
    }

    template <typename TEnumerator, typename TOtherEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TKeyComparer>
    void LeftJoinEnumerator<TEnumerator, TOtherEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TKeyComparer>::MoveNext()
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