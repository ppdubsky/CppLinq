#pragma once

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"
#include "Details/TypeTraits/FunctionReturnTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct AggregateMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        using ValueType = typename EnumeratorType::ValueType;

        template <typename TAccumulator>
        auto Aggregate(const TAccumulator accumulator) const -> ValueType;
        template <typename TAccumulator, typename TAccumulatorValue>
        auto Aggregate(const TAccumulatorValue seed, const TAccumulator accumulator) const -> TAccumulatorValue;
        template <typename TAccumulator, typename TAccumulatorValue, typename TResultSelector, typename TResultType = TypeTraits::FunctionReturnTypeProvider<TResultSelector, TAccumulatorValue>::ReturnType>
        auto Aggregate(const TAccumulatorValue seed, const TAccumulator accumulator, const TResultSelector resultSelector) const -> TResultType;
    };
}