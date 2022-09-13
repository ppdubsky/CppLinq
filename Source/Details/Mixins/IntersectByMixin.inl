#pragma once

#include "Details/Mixins/IntersectByMixin.hpp"

#include "Details/Comparers/DefaultEqualityComparer.hpp"
#include "Details/Enumerators/IntersectEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TIntersectEnumerator, typename TSelector>
    auto IntersectByMixin<TQuery>::IntersectBy(const Query<TIntersectEnumerator>& intersectQuery, const TSelector selector) const -> Query<Enumerators::IntersectEnumerator<EnumeratorType, TIntersectEnumerator, TSelector, Comparers::DefaultEqualityComparer<KeyType<TSelector>>>>
    {
        return IntersectBy(intersectQuery, selector, Comparers::DefaultEqualityComparer<KeyType<TSelector>>());
    }

    template <typename TQuery>
    template <typename TIntersectEnumerator, typename TSelector, typename TComparer>
    auto IntersectByMixin<TQuery>::IntersectBy(const Query<TIntersectEnumerator>& intersectQuery, const TSelector selector, const TComparer comparer) const -> Query<Enumerators::IntersectEnumerator<EnumeratorType, TIntersectEnumerator, TSelector, TComparer>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), intersectQuery.GetEnumerator(), selector, comparer } };
    }
}