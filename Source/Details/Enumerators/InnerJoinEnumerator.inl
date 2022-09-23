#pragma once

#include "Details/Enumerators/InnerJoinEnumerator.hpp"

#include "Exceptions/FinishedEnumeratorException.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TLeftEnumerator, typename TRightEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TKeyComparer>
    InnerJoinEnumerator<TLeftEnumerator, TRightEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TKeyComparer>::InnerJoinEnumerator(const TLeftEnumerator leftEnumerator, const TRightEnumerator rightEnumerator, const TLeftKeySelector leftKeySelector, const TRightKeySelector rightKeySelector, const TResultSelector resultSelector, const TKeyComparer keyComparer) :
        Base(leftEnumerator),
        container(bucketCount, HasherType(), keyComparer),
        leftKeySelector(leftKeySelector),
        resultSelector(resultSelector),
        rightEnumerator(rightEnumerator),
        rightKeySelector(rightKeySelector)
    {
    }

    template <typename TLeftEnumerator, typename TRightEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TKeyComparer>
    void InnerJoinEnumerator<TLeftEnumerator, TRightEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TKeyComparer>::EnsureContainerIsReady()
    {
        if (!isContainerReady)
        {
            while (rightEnumerator.HasCurrent())
            {
                const auto current = rightEnumerator.GetCurrent();
                const auto key = rightKeySelector(current);

                container.insert({ key, current });

                rightEnumerator.MoveNext();
            }

            isContainerReady = true;
        }
    }

    template <typename TLeftEnumerator, typename TRightEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TKeyComparer>
    void InnerJoinEnumerator<TLeftEnumerator, TRightEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TKeyComparer>::EnsureEnumeratorIsReady()
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
                for (auto iterator = range.first; iterator != range.second; ++iterator)
                {
                    queue.push(resultSelector(current, iterator->second));
                }

                Base::MoveNext();
            }

            isReady = true;
        }
    }

    template <typename TLeftEnumerator, typename TRightEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TKeyComparer>
    auto InnerJoinEnumerator<TLeftEnumerator, TRightEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TKeyComparer>::GetCurrent() -> ValueType
    {
        EnsureEnumeratorIsReady();

        if (queue.empty())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        return queue.front();
    }

    template <typename TLeftEnumerator, typename TRightEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TKeyComparer>
    auto InnerJoinEnumerator<TLeftEnumerator, TRightEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TKeyComparer>::HasCurrent() -> bool
    {
        EnsureEnumeratorIsReady();

        return !queue.empty();
    }

    template <typename TLeftEnumerator, typename TRightEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TKeyComparer>
    void InnerJoinEnumerator<TLeftEnumerator, TRightEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TKeyComparer>::MoveNext()
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