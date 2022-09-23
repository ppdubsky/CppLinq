#pragma once

#include "Details/Mixins/IntersectByMixin.hpp"

#include "Details/Comparers/DefaultEqualityComparer.hpp"
#include "Details/Enumerators/IntersectEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TIntersectEnumerator, typename TKeySelector>
    auto IntersectByMixin<TQuery>::IntersectBy(const Query<TIntersectEnumerator>& intersectQuery, const TKeySelector keySelector) const -> Query<Enumerators::IntersectEnumerator<EnumeratorType, TIntersectEnumerator, TKeySelector, Comparers::DefaultEqualityComparer<KeyType<TKeySelector>>>>
    {
        return IntersectBy(intersectQuery, keySelector, Comparers::DefaultEqualityComparer<KeyType<TKeySelector>>());
    }

    template <typename TQuery>
    template <typename TIntersectEnumerator, typename TKeySelector, typename TComparer>
    auto IntersectByMixin<TQuery>::IntersectBy(const Query<TIntersectEnumerator>& intersectQuery, const TKeySelector keySelector, const TComparer comparer) const -> Query<Enumerators::IntersectEnumerator<EnumeratorType, TIntersectEnumerator, TKeySelector, TComparer>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), intersectQuery.GetEnumerator(), keySelector, comparer } };
    }
}