#pragma once

#include "Details/Mixins/UnionByMixin.hpp"

#include "Details/Comparers/DefaultEqualityComparer.hpp"
#include "Details/Enumerators/UnionEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TUnionEnumerator, typename TKeySelector>
    auto UnionByMixin<TQuery>::UnionBy(const Query<TUnionEnumerator>& unionQuery, const TKeySelector keySelector) const -> Query<Enumerators::UnionEnumerator<EnumeratorType, TUnionEnumerator, TKeySelector, Comparers::DefaultEqualityComparer<KeyType<TKeySelector>>>>
    {
        return UnionBy(unionQuery, keySelector, Comparers::DefaultEqualityComparer<KeyType<TKeySelector>>());
    }

    template <typename TQuery>
    template <typename TUnionEnumerator, typename TKeySelector, typename TKeyComparer>
    auto UnionByMixin<TQuery>::UnionBy(const Query<TUnionEnumerator>& unionQuery, const TKeySelector keySelector, const TKeyComparer keyComparer) const -> Query<Enumerators::UnionEnumerator<EnumeratorType, TUnionEnumerator, TKeySelector, TKeyComparer>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), unionQuery.GetEnumerator(), keySelector, keyComparer } };
    }
}