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
    template <typename TSecondEnumerator>
    auto IntersectMixin<TQuery>::Intersect(const Query<TSecondEnumerator>& secondQuery) const -> Query<Enumerators::IntersectEnumerator<EnumeratorType, TSecondEnumerator, Selectors::SelfSelector<ValueType>, Comparers::DefaultEqualityComparer<ValueType>>>
    {
        return Intersect(secondQuery, Comparers::DefaultEqualityComparer<ValueType>());
    }

    template <typename TQuery>
    template <typename TSecondEnumerator, typename TComparer>
    auto IntersectMixin<TQuery>::Intersect(const Query<TSecondEnumerator>& secondQuery, const TComparer comparer) const -> Query<Enumerators::IntersectEnumerator<EnumeratorType, TSecondEnumerator, Selectors::SelfSelector<ValueType>, TComparer>>
    {
        return MixinUtilities::GetQuery<TQuery>(*this).IntersectBy(secondQuery, Selectors::SelfSelector<ValueType>(), comparer);
    }
}