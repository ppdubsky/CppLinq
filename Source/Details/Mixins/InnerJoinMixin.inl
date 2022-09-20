#pragma once

#include "Details/Mixins/InnerJoinMixin.hpp"

#include "Details/Enumerators/InnerJoinEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TOtherEnumerator, typename TSelector, typename TOtherSelector, typename TResultSelector>
    auto InnerJoinMixin<TQuery>::InnerJoin(const Query<TOtherEnumerator>& otherQuery, const TSelector selector, const TOtherSelector otherSelector, const TResultSelector resultSelector) const -> Query<Enumerators::InnerJoinEnumerator<EnumeratorType, TOtherEnumerator, TSelector, TOtherSelector, TResultSelector, Comparers::DefaultEqualityComparer<KeyType<TSelector>>>>
    {
        return InnerJoin(otherQuery, selector, otherSelector, resultSelector, Comparers::DefaultEqualityComparer<KeyType<TSelector>>());
    }

    template <typename TQuery>
    template <typename TOtherEnumerator, typename TSelector, typename TOtherSelector, typename TResultSelector, typename TComparer>
    auto InnerJoinMixin<TQuery>::InnerJoin(const Query<TOtherEnumerator>& otherQuery, const TSelector selector, const TOtherSelector otherSelector, const TResultSelector resultSelector, const TComparer comparer) const -> Query<Enumerators::InnerJoinEnumerator<EnumeratorType, TOtherEnumerator, TSelector, TOtherSelector, TResultSelector, TComparer>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), otherQuery.GetEnumerator(), selector, otherSelector, resultSelector, comparer } };
    }
}