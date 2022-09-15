#pragma once

#include "Details/Comparers/DefaultEqualityComparer.Forward.hpp"
#include "Details/Enumerators/UnionEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include <type_traits>

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct UnionByMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        using ValueType = typename EnumeratorType::ValueType;
        template <typename TSelector>
        using KeyType = decltype(std::declval<TSelector>()(std::declval<ValueType>()));

        template <typename TUnionEnumerator, typename TSelector>
        auto UnionBy(const Query<TUnionEnumerator>& unionQuery, const TSelector selector) const -> Query<Enumerators::UnionEnumerator<EnumeratorType, TUnionEnumerator, TSelector, Comparers::DefaultEqualityComparer<KeyType<TSelector>>>>;
        template <typename TUnionEnumerator, typename TSelector, typename TComparer>
        auto UnionBy(const Query<TUnionEnumerator>& unionQuery, const TSelector selector, const TComparer comparer) const -> Query<Enumerators::UnionEnumerator<EnumeratorType, TUnionEnumerator, TSelector, TComparer>>;
    };
}