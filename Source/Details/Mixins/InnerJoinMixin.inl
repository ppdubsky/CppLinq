#pragma once

#include "Details/Mixins/InnerJoinMixin.hpp"

#include "Details/Enumerators/InnerJoinEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TOtherEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector>
    auto InnerJoinMixin<TQuery>::InnerJoin(const Query<TOtherEnumerator>& otherQuery, const TLeftKeySelector leftKeySelector, const TRightKeySelector rightKeySelector, const TResultSelector resultSelector) const -> Query<Enumerators::InnerJoinEnumerator<EnumeratorType, TOtherEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, Comparers::DefaultEqualityComparer<KeyType<TLeftKeySelector>>>>
    {
        return InnerJoin(otherQuery, leftKeySelector, rightKeySelector, resultSelector, Comparers::DefaultEqualityComparer<KeyType<TLeftKeySelector>>());
    }

    template <typename TQuery>
    template <typename TOtherEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TKeyComparer>
    auto InnerJoinMixin<TQuery>::InnerJoin(const Query<TOtherEnumerator>& otherQuery, const TLeftKeySelector leftKeySelector, const TRightKeySelector rightKeySelector, const TResultSelector resultSelector, const TKeyComparer keyComparer) const -> Query<Enumerators::InnerJoinEnumerator<EnumeratorType, TOtherEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TKeyComparer>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), otherQuery.GetEnumerator(), leftKeySelector, rightKeySelector, resultSelector, keyComparer } };
    }
}