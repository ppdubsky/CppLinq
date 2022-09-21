#pragma once

#include "Details/Mixins/LeftJoinMixin.hpp"

#include "Details/Enumerators/LeftJoinEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TOtherEnumerator, typename TSelector, typename TOtherSelector, typename TResultSelector>
    auto LeftJoinMixin<TQuery>::LeftJoin(const Query<TOtherEnumerator>& otherQuery, const TSelector selector, const TOtherSelector otherSelector, const TResultSelector resultSelector) const -> Query<Enumerators::LeftJoinEnumerator<EnumeratorType, TOtherEnumerator, TSelector, TOtherSelector, TResultSelector, Comparers::DefaultEqualityComparer<KeyType<TSelector>>>>
    {
        return LeftJoin(otherQuery, selector, otherSelector, resultSelector, Comparers::DefaultEqualityComparer<KeyType<TSelector>>());
    }

    template <typename TQuery>
    template <typename TOtherEnumerator, typename TSelector, typename TOtherSelector, typename TResultSelector, typename TComparer>
    auto LeftJoinMixin<TQuery>::LeftJoin(const Query<TOtherEnumerator>& otherQuery, const TSelector selector, const TOtherSelector otherSelector, const TResultSelector resultSelector, const TComparer comparer) const -> Query<Enumerators::LeftJoinEnumerator<EnumeratorType, TOtherEnumerator, TSelector, TOtherSelector, TResultSelector, TComparer>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), otherQuery.GetEnumerator(), selector, otherSelector, resultSelector, comparer } };
    }
}