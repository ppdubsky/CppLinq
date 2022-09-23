#pragma once

#include "Details/Mixins/UnionByMixin.hpp"

#include "Details/Comparers/DefaultEqualityComparer.hpp"
#include "Details/Enumerators/UnionEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TSecondEnumerator, typename TKeySelector>
    auto UnionByMixin<TQuery>::UnionBy(const Query<TSecondEnumerator>& secondQuery, const TKeySelector keySelector) const -> Query<Enumerators::UnionEnumerator<EnumeratorType, TSecondEnumerator, TKeySelector, Comparers::DefaultEqualityComparer<KeyType<TKeySelector>>>>
    {
        return UnionBy(secondQuery, keySelector, Comparers::DefaultEqualityComparer<KeyType<TKeySelector>>());
    }

    template <typename TQuery>
    template <typename TSecondEnumerator, typename TKeySelector, typename TKeyComparer>
    auto UnionByMixin<TQuery>::UnionBy(const Query<TSecondEnumerator>& secondQuery, const TKeySelector keySelector, const TKeyComparer keyComparer) const -> Query<Enumerators::UnionEnumerator<EnumeratorType, TSecondEnumerator, TKeySelector, TKeyComparer>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), secondQuery.GetEnumerator(), keySelector, keyComparer } };
    }
}