#pragma once

#include "Details/Comparers/DefaultEqualityComparer.Forward.hpp"
#include "Details/Enumerators/DistinctEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"
#include "Details/TypeTraits/FunctionReturnTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct DistinctByMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        using ValueType = typename EnumeratorType::ValueType;
        template <typename TKeySelector>
        using KeyType = TypeTraits::FunctionReturnTypeProvider<TKeySelector, ValueType>::ReturnType;

        template <typename TKeySelector>
        auto DistinctBy(const TKeySelector keySelector) const -> Query<Enumerators::DistinctEnumerator<EnumeratorType, TKeySelector, Comparers::DefaultEqualityComparer<KeyType<TKeySelector>>>>;
        template <typename TKeySelector, typename TKeyComparer>
        auto DistinctBy(const TKeySelector keySelector, const TKeyComparer keyComparer) const -> Query<Enumerators::DistinctEnumerator<EnumeratorType, TKeySelector, TKeyComparer>>;
    };
}