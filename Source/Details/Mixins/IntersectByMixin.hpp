#pragma once

#include "Details/Comparers/DefaultEqualityComparer.Forward.hpp"
#include "Details/Enumerators/IntersectEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"
#include "Details/TypeTraits/FunctionReturnTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct IntersectByMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        using ValueType = typename EnumeratorType::ValueType;
        template <typename TKeySelector>
        using KeyType = TypeTraits::FunctionReturnTypeProvider<TKeySelector, ValueType>::ReturnType;

        template <typename TSecondEnumerator, typename TKeySelector>
        auto IntersectBy(const Query<TSecondEnumerator>& secondQuery, const TKeySelector keySelector) const -> Query<Enumerators::IntersectEnumerator<EnumeratorType, TSecondEnumerator, TKeySelector, Comparers::DefaultEqualityComparer<KeyType<TKeySelector>>>>;
        template <typename TSecondEnumerator, typename TKeySelector, typename TKeyComparer>
        auto IntersectBy(const Query<TSecondEnumerator>& secondQuery, const TKeySelector keySelector, const TKeyComparer keyComparer) const -> Query<Enumerators::IntersectEnumerator<EnumeratorType, TSecondEnumerator, TKeySelector, TKeyComparer>>;
    };
}