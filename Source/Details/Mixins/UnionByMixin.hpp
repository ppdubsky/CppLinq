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
        template <typename TKeySelector>
        using KeyType = decltype(std::declval<TKeySelector>()(std::declval<ValueType>()));

        template <typename TUnionEnumerator, typename TKeySelector>
        auto UnionBy(const Query<TUnionEnumerator>& unionQuery, const TKeySelector keySelector) const -> Query<Enumerators::UnionEnumerator<EnumeratorType, TUnionEnumerator, TKeySelector, Comparers::DefaultEqualityComparer<KeyType<TKeySelector>>>>;
        template <typename TUnionEnumerator, typename TKeySelector, typename TKeyComparer>
        auto UnionBy(const Query<TUnionEnumerator>& unionQuery, const TKeySelector keySelector, const TKeyComparer keyComparer) const -> Query<Enumerators::UnionEnumerator<EnumeratorType, TUnionEnumerator, TKeySelector, TKeyComparer>>;
    };
}