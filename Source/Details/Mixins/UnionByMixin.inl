#pragma once

#include "Details/Mixins/UnionByMixin.hpp"

#include "Details/Comparers/DefaultEqualityComparer.hpp"
#include "Details/Enumerators/UnionEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TUnionEnumerator, typename TSelector>
    auto UnionByMixin<TQuery>::UnionBy(const Query<TUnionEnumerator>& unionQuery, const TSelector selector) const -> Query<Enumerators::UnionEnumerator<EnumeratorType, TUnionEnumerator, TSelector, Comparers::DefaultEqualityComparer<KeyType<TSelector>>>>
    {
        return UnionBy(unionQuery, selector, Comparers::DefaultEqualityComparer<KeyType<TSelector>>());
    }

    template <typename TQuery>
    template <typename TUnionEnumerator, typename TSelector, typename TComparer>
    auto UnionByMixin<TQuery>::UnionBy(const Query<TUnionEnumerator>& unionQuery, const TSelector selector, const TComparer comparer) const -> Query<Enumerators::UnionEnumerator<EnumeratorType, TUnionEnumerator, TSelector, TComparer>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), unionQuery.GetEnumerator(), selector, comparer } };
    }
}