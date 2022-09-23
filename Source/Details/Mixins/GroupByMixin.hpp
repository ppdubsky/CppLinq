#pragma once

#include "Details/Comparers/DefaultEqualityComparer.Forward.hpp"
#include "Details/Enumerators/GroupEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"
#include "Details/TypeTraits/FunctionReturnTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct GroupByMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        using ValueType = typename EnumeratorType::ValueType;
        template <typename TKeySelector>
        using KeyType = TypeTraits::FunctionReturnTypeProvider<TKeySelector, ValueType>::ReturnType;

        template <typename TKeySelector, typename TElementSelector, typename TResultSelector>
        auto GroupBy(const TKeySelector keySelector, const TElementSelector elementSelector, const TResultSelector resultSelector) -> Query<Enumerators::GroupEnumerator<EnumeratorType, TKeySelector, TElementSelector, TResultSelector, Comparers::DefaultEqualityComparer<KeyType<TKeySelector>>>>;
        template <typename TKeySelector, typename TElementSelector, typename TResultSelector, typename TKeyComparer>
        auto GroupBy(const TKeySelector keySelector, const TElementSelector elementSelector, const TResultSelector resultSelector, const TKeyComparer keyComparer) -> Query<Enumerators::GroupEnumerator<EnumeratorType, TKeySelector, TElementSelector, TResultSelector, TKeyComparer>>;
    };
}