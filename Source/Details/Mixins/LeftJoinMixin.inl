#pragma once

#include "Details/Mixins/LeftJoinMixin.hpp"

#include "Details/Enumerators/LeftJoinEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TRightEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector>
    auto LeftJoinMixin<TQuery>::LeftJoin(const Query<TRightEnumerator>& rightQuery, const TLeftKeySelector leftKeySelector, const TRightKeySelector rightKeySelector, const TResultSelector resultSelector) const -> Query<Enumerators::LeftJoinEnumerator<EnumeratorType, TRightEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, Comparers::DefaultEqualityComparer<KeyType<TLeftKeySelector>>>>
    {
        return LeftJoin(rightQuery, leftKeySelector, rightKeySelector, resultSelector, Comparers::DefaultEqualityComparer<KeyType<TLeftKeySelector>>());
    }

    template <typename TQuery>
    template <typename TRightEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TKeyComparer>
    auto LeftJoinMixin<TQuery>::LeftJoin(const Query<TRightEnumerator>& rightQuery, const TLeftKeySelector leftKeySelector, const TRightKeySelector rightKeySelector, const TResultSelector resultSelector, const TKeyComparer keyComparer) const -> Query<Enumerators::LeftJoinEnumerator<EnumeratorType, TRightEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TKeyComparer>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), rightQuery.GetEnumerator(), leftKeySelector, rightKeySelector, resultSelector, keyComparer } };
    }
}