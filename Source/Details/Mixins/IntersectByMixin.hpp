#pragma once

#include "Details/Comparers/DefaultEqualityComparer.Forward.hpp"
#include "Details/Enumerators/IntersectEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include <type_traits>

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct IntersectByMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        using ValueType = typename EnumeratorType::ValueType;
        template <typename TSelector>
        using KeyType = decltype(std::declval<TSelector>()(std::declval<ValueType>()));

        template <typename TIntersectEnumerator, typename TSelector>
        auto IntersectBy(const Query<TIntersectEnumerator>& intersectQuery, const TSelector selector) const -> Query<Enumerators::IntersectEnumerator<EnumeratorType, TIntersectEnumerator, TSelector, Comparers::DefaultEqualityComparer<KeyType<TSelector>>>>;
        template <typename TIntersectEnumerator, typename TSelector, typename TComparer>
        auto IntersectBy(const Query<TIntersectEnumerator>& intersectQuery, const TSelector selector, const TComparer comparer) const -> Query<Enumerators::IntersectEnumerator<EnumeratorType, TIntersectEnumerator, TSelector, TComparer>>;
    };
}