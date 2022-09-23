#pragma once

#include "Details/Enumerators/LeftJoinEnumerator.hpp"

#include "Exceptions/FinishedEnumeratorException.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TOtherEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TComparer>
    LeftJoinEnumerator<TEnumerator, TOtherEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TComparer>::LeftJoinEnumerator(const TEnumerator enumerator, const TOtherEnumerator otherEnumerator, const TLeftKeySelector leftKeySelector, const TRightKeySelector rightKeySelector, const TResultSelector resultSelector, const TComparer comparer) :
        Base(enumerator),
        container(bucketCount, HasherType(), comparer),
        leftKeySelector(leftKeySelector),
        otherEnumerator(otherEnumerator),
        resultSelector(resultSelector),
        rightKeySelector(rightKeySelector)
    {
    }

    template <typename TEnumerator, typename TOtherEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TComparer>
    void LeftJoinEnumerator<TEnumerator, TOtherEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TComparer>::EnsureContainerIsReady()
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

    template <typename TEnumerator, typename TOtherEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TComparer>
    void LeftJoinEnumerator<TEnumerator, TOtherEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TComparer>::EnsureEnumeratorIsReady()
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

    template <typename TEnumerator, typename TOtherEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TComparer>
    auto LeftJoinEnumerator<TEnumerator, TOtherEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TComparer>::GetCurrent() -> ValueType
    {
        EnsureEnumeratorIsReady();

        if (queue.empty())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        return queue.front();
    }

    template <typename TEnumerator, typename TOtherEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TComparer>
    auto LeftJoinEnumerator<TEnumerator, TOtherEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TComparer>::HasCurrent() -> bool
    {
        EnsureEnumeratorIsReady();

        return !queue.empty();
    }

    template <typename TEnumerator, typename TOtherEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TComparer>
    void LeftJoinEnumerator<TEnumerator, TOtherEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TComparer>::MoveNext()
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