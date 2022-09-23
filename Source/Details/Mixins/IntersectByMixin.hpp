#pragma once

#include "Details/Comparers/DefaultEqualityComparer.Forward.hpp"
#include "Details/Enumerators/IntersectEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include <type_traits>

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct IntersectByMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        using ValueType = typename EnumeratorType::ValueType;
        template <typename TKeySelector>
        using KeyType = decltype(std::declval<TKeySelector>()(std::declval<ValueType>()));

        template <typename TSecondEnumerator, typename TKeySelector>
        auto IntersectBy(const Query<TSecondEnumerator>& secondQuery, const TKeySelector keySelector) const -> Query<Enumerators::IntersectEnumerator<EnumeratorType, TSecondEnumerator, TKeySelector, Comparers::DefaultEqualityComparer<KeyType<TKeySelector>>>>;
        template <typename TSecondEnumerator, typename TKeySelector, typename TKeyComparer>
        auto IntersectBy(const Query<TSecondEnumerator>& secondQuery, const TKeySelector keySelector, const TKeyComparer keyComparer) const -> Query<Enumerators::IntersectEnumerator<EnumeratorType, TSecondEnumerator, TKeySelector, TKeyComparer>>;
    };
}