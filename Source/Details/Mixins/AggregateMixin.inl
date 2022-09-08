#pragma once

#include "Details/Mixins/AggregateMixin.hpp"

#include "Details/Mixins/MixinUtilities.hpp"
#include "Exceptions/EmptyContainerException.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TAccumulator>
    auto AggregateMixin<TQuery>::Aggregate(const TAccumulator accumulator) const -> ValueType
    {
        EnumeratorType enumerator = MixinUtilities::GetEnumerator<TQuery>(*this);
        if (!enumerator.HasCurrent())
        {
            throw Exceptions::EmptyContainerException();
        }

        ValueType aggregatedValue = enumerator.GetCurrent();

        do
        {
            enumerator.MoveNext();

            if (!enumerator.HasCurrent())
            {
                break;
            }

            aggregatedValue = accumulator(aggregatedValue, enumerator.GetCurrent());
        } while (true);

        return aggregatedValue;
    }

    template <typename TQuery>
    template <typename TAccumulator, typename TAccumulatorValue>
    auto AggregateMixin<TQuery>::Aggregate(const TAccumulatorValue seed, const TAccumulator accumulator) const -> TAccumulatorValue
    {
        TAccumulatorValue aggregatedValue = seed;

        for (const ValueType& value : MixinUtilities::GetQuery<TQuery>(*this))
        {
            aggregatedValue = accumulator(aggregatedValue, value);
        }

        return aggregatedValue;
    }

    template <typename TQuery>
    template <typename TAccumulator, typename TAccumulatorValue, typename TResultSelector, typename TResultType>
    auto AggregateMixin<TQuery>::Aggregate(const TAccumulatorValue seed, const TAccumulator accumulator, const TResultSelector resultSelector) const -> TResultType
    {
        return resultSelector(Aggregate(seed, accumulator));
    }
}