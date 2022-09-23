#pragma once

#include "Details/Mixins/OuterJoinMixin.hpp"

#include "Details/Enumerators/OuterJoinEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TOtherEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector>
    auto OuterJoinMixin<TQuery>::OuterJoin(const Query<TOtherEnumerator>& otherQuery, const TLeftKeySelector leftKeySelector, const TRightKeySelector rightKeySelector, const TResultSelector resultSelector) const -> Query<Enumerators::OuterJoinEnumerator<EnumeratorType, TOtherEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, Comparers::DefaultEqualityComparer<KeyType<TLeftKeySelector>>>>
    {
        return OuterJoin(otherQuery, leftKeySelector, rightKeySelector, resultSelector, Comparers::DefaultEqualityComparer<KeyType<TLeftKeySelector>>());
    }

    template <typename TQuery>
    template <typename TOtherEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TKeyComparer>
    auto OuterJoinMixin<TQuery>::OuterJoin(const Query<TOtherEnumerator>& otherQuery, const TLeftKeySelector leftKeySelector, const TRightKeySelector rightKeySelector, const TResultSelector resultSelector, const TKeyComparer keyComparer) const -> Query<Enumerators::OuterJoinEnumerator<EnumeratorType, TOtherEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TKeyComparer>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), otherQuery.GetEnumerator(), leftKeySelector, rightKeySelector, resultSelector, keyComparer } };
    }
}