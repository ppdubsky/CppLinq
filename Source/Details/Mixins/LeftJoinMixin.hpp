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
        template <typename TSelector>
        using KeyType = decltype(std::declval<TSelector>()(std::declval<ValueType>()));

        template <typename TOtherEnumerator, typename TSelector, typename TOtherSelector, typename TResultSelector>
        auto LeftJoin(const Query<TOtherEnumerator>& otherQuery, const TSelector selector, const TOtherSelector otherSelector, const TResultSelector resultSelector) const -> Query<Enumerators::LeftJoinEnumerator<EnumeratorType, TOtherEnumerator, TSelector, TOtherSelector, TResultSelector, Comparers::DefaultEqualityComparer<KeyType<TSelector>>>>;
        template <typename TOtherEnumerator, typename TSelector, typename TOtherSelector, typename TResultSelector, typename TComparer>
        auto LeftJoin(const Query<TOtherEnumerator>& otherQuery, const TSelector selector, const TOtherSelector otherSelector, const TResultSelector resultSelector, const TComparer comparer) const -> Query<Enumerators::LeftJoinEnumerator<EnumeratorType, TOtherEnumerator, TSelector, TOtherSelector, TResultSelector, TComparer>>;
    };
}