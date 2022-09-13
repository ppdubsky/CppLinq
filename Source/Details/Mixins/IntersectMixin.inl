#pragma once

#include "Details/Mixins/IntersectMixin.hpp"

#include "Details/Comparers/DefaultEqualityComparer.hpp"
#include "Details/Enumerators/IntersectEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"
#include "Details/Selectors/SelfSelector.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TIntersectEnumerator>
    auto IntersectMixin<TQuery>::Intersect(const Query<TIntersectEnumerator>& intersectQuery) const -> Query<Enumerators::IntersectEnumerator<EnumeratorType, TIntersectEnumerator, Selectors::SelfSelector<ValueType>, Comparers::DefaultEqualityComparer<ValueType>>>
    {
        return Intersect(intersectQuery, Comparers::DefaultEqualityComparer<ValueType>());
    }

    template <typename TQuery>
    template <typename TIntersectEnumerator, typename TComparer>
    auto IntersectMixin<TQuery>::Intersect(const Query<TIntersectEnumerator>& intersectQuery, const TComparer comparer) const -> Query<Enumerators::IntersectEnumerator<EnumeratorType, TIntersectEnumerator, Selectors::SelfSelector<ValueType>, TComparer>>
    {
        return MixinUtilities::GetQuery<TQuery>(*this).IntersectBy(intersectQuery, Selectors::SelfSelector<ValueType>(), comparer);
    }
}