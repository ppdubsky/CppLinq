#pragma once

#include "Details/Enumerators/OuterJoinEnumerator.hpp"

#include <algorithm>

#include "Exceptions/FinishedEnumeratorException.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TOtherEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TComparer>
    OuterJoinEnumerator<TEnumerator, TOtherEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TComparer>::OuterJoinEnumerator(const TEnumerator enumerator, const TOtherEnumerator otherEnumerator, const TLeftKeySelector leftKeySelector, const TRightKeySelector rightKeySelector, const TResultSelector resultSelector, const TComparer comparer) :
        Base(enumerator),
        container(bucketCount, HasherType(), comparer),
        leftKeySelector(leftKeySelector),
        otherEnumerator(otherEnumerator),
        resultSelector(resultSelector),
        rightKeySelector(rightKeySelector)
    {
    }

    template <typename TEnumerator, typename TOtherEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TComparer>
    void OuterJoinEnumerator<TEnumerator, TOtherEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TComparer>::EnsureContainerIsReady()
    {
        if (!isContainerReady)
        {
            while (otherEnumerator.HasCurrent())
            {
                const auto current = otherEnumerator.GetCurrent();
                const auto key = rightKeySelector(current);

                container.insert({ key, { static_cast<std::int32_t>(usedValues.size()), current } });
                usedValues.push_back({ false, current });

                otherEnumerator.MoveNext();
            }

            isContainerReady = true;
        }
    }

    template <typename TEnumerator, typename TOtherEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TComparer>
    void OuterJoinEnumerator<TEnumerator, TOtherEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TComparer>::EnsureEnumeratorIsReady()
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

    template <typename TEnumerator, typename TOtherEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TComparer>
    auto OuterJoinEnumerator<TEnumerator, TOtherEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TComparer>::GetCurrent() -> ValueType
    {
        EnsureEnumeratorIsReady();

        if (queue.empty() && usedValues.empty())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        return queue.empty() ? resultSelector(std::nullopt, { usedValues.front().value }) : queue.front();
    }

    template <typename TEnumerator, typename TOtherEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TComparer>
    auto OuterJoinEnumerator<TEnumerator, TOtherEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TComparer>::HasCurrent() -> bool
    {
        EnsureEnumeratorIsReady();

        return !queue.empty() || !usedValues.empty();
    }

    template <typename TEnumerator, typename TOtherEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TComparer>
    void OuterJoinEnumerator<TEnumerator, TOtherEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TComparer>::MoveNext()
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