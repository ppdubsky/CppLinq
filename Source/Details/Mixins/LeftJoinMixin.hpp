#pragma once

#include "Details/Comparers/DefaultEqualityComparer.Forward.hpp"
#include "Details/Enumerators/LeftJoinEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include <type_traits>

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct LeftJoinMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        using ValueType = typename EnumeratorType::ValueType;
        template <typename TKeySelector>
        using KeyType = decltype(std::declval<TKeySelector>()(std::declval<ValueType>()));

        template <typename TOtherEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector>
        auto LeftJoin(const Query<TOtherEnumerator>& otherQuery, const TLeftKeySelector leftKeySelector, const TRightKeySelector rightKeySelector, const TResultSelector resultSelector) const -> Query<Enumerators::LeftJoinEnumerator<EnumeratorType, TOtherEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, Comparers::DefaultEqualityComparer<KeyType<TLeftKeySelector>>>>;
        template <typename TOtherEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TKeyComparer>
        auto LeftJoin(const Query<TOtherEnumerator>& otherQuery, const TLeftKeySelector leftKeySelector, const TRightKeySelector rightKeySelector, const TResultSelector resultSelector, const TKeyComparer keyComparer) const -> Query<Enumerators::LeftJoinEnumerator<EnumeratorType, TOtherEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TKeyComparer>>;
    };
}