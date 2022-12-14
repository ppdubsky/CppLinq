#pragma once

#include "Details/Comparers/DefaultEqualityComparer.Forward.hpp"
#include "Details/Enumerators/UnionEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"
#include "Details/TypeTraits/FunctionReturnTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct UnionByMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        using ValueType = typename EnumeratorType::ValueType;
        template <typename TKeySelector>
        using KeyType = TypeTraits::FunctionReturnTypeProvider<TKeySelector, ValueType>::ReturnType;

        template <typename TSecondEnumerator, typename TKeySelector>
        auto UnionBy(const Query<TSecondEnumerator>& secondQuery, const TKeySelector keySelector) const -> Query<Enumerators::UnionEnumerator<EnumeratorType, TSecondEnumerator, TKeySelector, Comparers::DefaultEqualityComparer<KeyType<TKeySelector>>>>;
        template <typename TSecondEnumerator, typename TKeySelector, typename TKeyComparer>
        auto UnionBy(const Query<TSecondEnumerator>& secondQuery, const TKeySelector keySelector, const TKeyComparer keyComparer) const -> Query<Enumerators::UnionEnumerator<EnumeratorType, TSecondEnumerator, TKeySelector, TKeyComparer>>;
    };
}