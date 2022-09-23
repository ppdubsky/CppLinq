#pragma once

#include "Details/Mixins/UnionMixin.hpp"

#include "Details/Comparers/DefaultEqualityComparer.hpp"
#include "Details/Enumerators/UnionEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"
#include "Details/Selectors/SelfSelector.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TSecondEnumerator>
    auto UnionMixin<TQuery>::Union(const Query<TSecondEnumerator>& secondQuery) const -> Query<Enumerators::UnionEnumerator<EnumeratorType, TSecondEnumerator, Selectors::SelfSelector<ValueType>, Comparers::DefaultEqualityComparer<ValueType>>>
    {
        return Union(secondQuery, Comparers::DefaultEqualityComparer<ValueType>());
    }

    template <typename TQuery>
    template <typename TSecondEnumerator, typename TComparer>
    auto UnionMixin<TQuery>::Union(const Query<TSecondEnumerator>& secondQuery, const TComparer comparer) const -> Query<Enumerators::UnionEnumerator<EnumeratorType, TSecondEnumerator, Selectors::SelfSelector<ValueType>, TComparer>>
    {
        return MixinUtilities::GetQuery<TQuery>(*this).UnionBy(secondQuery, Selectors::SelfSelector<ValueType>(), comparer);
    }
}