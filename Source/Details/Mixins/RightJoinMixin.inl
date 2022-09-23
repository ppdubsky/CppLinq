#pragma once

#include "Details/Mixins/RightJoinMixin.hpp"

#include "Details/Enumerators/RightJoinEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TOtherEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector>
    auto RightJoinMixin<TQuery>::RightJoin(const Query<TOtherEnumerator>& otherQuery, const TLeftKeySelector leftKeySelector, const TRightKeySelector rightKeySelector, const TResultSelector resultSelector) const -> Query<Enumerators::RightJoinEnumerator<EnumeratorType, TOtherEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, Comparers::DefaultEqualityComparer<KeyType<TLeftKeySelector>>>>
    {
        return RightJoin(otherQuery, leftKeySelector, rightKeySelector, resultSelector, Comparers::DefaultEqualityComparer<KeyType<TLeftKeySelector>>());
    }

    template <typename TQuery>
    template <typename TOtherEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TComparer>
    auto RightJoinMixin<TQuery>::RightJoin(const Query<TOtherEnumerator>& otherQuery, const TLeftKeySelector leftKeySelector, const TRightKeySelector rightKeySelector, const TResultSelector resultSelector, const TComparer comparer) const -> Query<Enumerators::RightJoinEnumerator<EnumeratorType, TOtherEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TComparer>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), otherQuery.GetEnumerator(), leftKeySelector, rightKeySelector, resultSelector, comparer } };
    }
}