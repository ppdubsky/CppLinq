#pragma once

#include <type_traits>

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct AggregateMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        template <typename TAccumulatorValue, typename TResultSelector>
        using ResultType = decltype(std::declval<TResultSelector>()(std::declval<TAccumulatorValue>()));
        using ValueType = typename EnumeratorType::ValueType;

        template <typename TAccumulator>
        auto Aggregate(const TAccumulator accumulator) const -> ValueType;
        template <typename TAccumulator, typename TAccumulatorValue>
        auto Aggregate(const TAccumulatorValue seed, const TAccumulator accumulator) const -> TAccumulatorValue;
        template <typename TAccumulator, typename TAccumulatorValue, typename TResultSelector, typename TResultType = ResultType<TAccumulatorValue, TResultSelector>>
        auto Aggregate(const TAccumulatorValue seed, const TAccumulator accumulator, const TResultSelector resultSelector) const -> TResultType;
    };
}