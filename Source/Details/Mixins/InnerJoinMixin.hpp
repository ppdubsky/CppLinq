#pragma once

#include "Details/Comparers/DefaultEqualityComparer.Forward.hpp"
#include "Details/Enumerators/InnerJoinEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"
#include "Details/TypeTraits/FunctionReturnTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct InnerJoinMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        using ValueType = typename EnumeratorType::ValueType;
        template <typename TKeySelector>
        using KeyType = TypeTraits::FunctionReturnTypeProvider<TKeySelector, ValueType>::ReturnType;

        template <typename TRightEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector>
        auto InnerJoin(const Query<TRightEnumerator>& rightQuery, const TLeftKeySelector leftKeySelector, const TRightKeySelector rightKeySelector, const TResultSelector resultSelector) const -> Query<Enumerators::InnerJoinEnumerator<EnumeratorType, TRightEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, Comparers::DefaultEqualityComparer<KeyType<TLeftKeySelector>>>>;
        template <typename TRightEnumerator, typename TLeftKeySelector, typename TRightKeySelector, typename TResultSelector, typename TKeyComparer>
        auto InnerJoin(const Query<TRightEnumerator>& rightQuery, const TLeftKeySelector leftKeySelector, const TRightKeySelector rightKeySelector, const TResultSelector resultSelector, const TKeyComparer keyComparer) const -> Query<Enumerators::InnerJoinEnumerator<EnumeratorType, TRightEnumerator, TLeftKeySelector, TRightKeySelector, TResultSelector, TKeyComparer>>;
    };
}