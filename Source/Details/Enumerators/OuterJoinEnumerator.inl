#pragma once

#include "Details/Enumerators/OuterJoinEnumerator.hpp"

#include <algorithm>

#include "Exceptions/FinishedEnumeratorException.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TLeftEnumerator, typename TRightEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TKeyComparer>
    OuterJoinEnumerator<TLeftEnumerator, TRightEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TKeyComparer>::OuterJoinEnumerator(const TLeftEnumerator leftEnumerator, const TRightEnumerator rightEnumerator, const TLeftKeySelector leftKeySelector, const TRightKeySelector rightKeySelector, const TResultSelector resultSelector, const TKeyComparer keyComparer) :
        Base(leftEnumerator),
        container(bucketCount, HasherType(), keyComparer),
        leftKeySelector(leftKeySelector),
        resultSelector(resultSelector),
        rightEnumerator(rightEnumerator),
        rightKeySelector(rightKeySelector)
    {
    }

    template <typename TLeftEnumerator, typename TRightEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TKeyComparer>
    void OuterJoinEnumerator<TLeftEnumerator, TRightEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TKeyComparer>::EnsureContainerIsReady()
    {
        if (!isContainerReady)
        {
            while (rightEnumerator.HasCurrent())
            {
                const auto current = rightEnumerator.GetCurrent();
                const auto key = rightKeySelector(current);

                container.insert({ key, { static_cast<std::int32_t>(usedValues.size()), current } });
                usedValues.push_back({ false, current });

                rightEnumerator.MoveNext();
            }

            isContainerReady = true;
        }
    }

    template <typename TLeftEnumerator, typename TRightEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TKeyComparer>
    void OuterJoinEnumerator<TLeftEnumerator, TRightEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TKeyComparer>::EnsureEnumeratorIsReady()
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
                        queue.push(resultSelector(current, iterator->second.value));
                        usedValues[iterator->second.index].isUsed = true;
                    }
                }

                Base::MoveNext();
            }

            if (queue.empty() && !Base::HasCurrent())
            {
                usedValues.erase(
                    std::remove_if(usedValues.begin(), usedValues.end(), [](const auto& info){ return info.isUsed; }),
                    usedValues.end()
                );
            }

            isReady = true;
        }
    }

    template <typename TLeftEnumerator, typename TRightEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TKeyComparer>
    auto OuterJoinEnumerator<TLeftEnumerator, TRightEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TKeyComparer>::GetCurrent() -> ValueType
    {
        EnsureEnumeratorIsReady();

        if (queue.empty() && usedValues.empty())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        return queue.empty() ? resultSelector(std::nullopt, { usedValues.front().value }) : queue.front();
    }

    template <typename TLeftEnumerator, typename TRightEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TKeyComparer>
    auto OuterJoinEnumerator<TLeftEnumerator, TRightEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TKeyComparer>::HasCurrent() -> bool
    {
        EnsureEnumeratorIsReady();

        return !queue.empty() || !usedValues.empty();
    }

    template <typename TLeftEnumerator, typename TRightEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TKeyComparer>
    void OuterJoinEnumerator<TLeftEnumerator, TRightEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TKeyComparer>::MoveNext()
    {
        if (queue.empty() && usedValues.empty())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        if (queue.empty())
        {
            usedValues.erase(usedValues.begin());
        }
        else
        {
            queue.pop();

            if (queue.empty())
            {
                isReady = false;

                EnsureEnumeratorIsReady();
            }
        }
    }
}