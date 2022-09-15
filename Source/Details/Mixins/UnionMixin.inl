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
    template <typename TUnionEnumerator>
    auto UnionMixin<TQuery>::Union(const Query<TUnionEnumerator>& unionQuery) const -> Query<Enumerators::UnionEnumerator<EnumeratorType, TUnionEnumerator, Selectors::SelfSelector<ValueType>, Comparers::DefaultEqualityComparer<ValueType>>>
    {
        return Union(unionQuery, Comparers::DefaultEqualityComparer<ValueType>());
    }

    template <typename TQuery>
    template <typename TUnionEnumerator, typename TComparer>
    auto UnionMixin<TQuery>::Union(const Query<TUnionEnumerator>& unionQuery, const TComparer comparer) const -> Query<Enumerators::UnionEnumerator<EnumeratorType, TUnionEnumerator, Selectors::SelfSelector<ValueType>, TComparer>>
    {
        return MixinUtilities::GetQuery<TQuery>(*this).UnionBy(unionQuery, Selectors::SelfSelector<ValueType>(), comparer);
    }
}