#pragma once

#include "Details/Comparers/DefaultEqualityComparer.Forward.hpp"
#include "Details/Enumerators/DistinctEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include <type_traits>

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct DistinctByMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        using ValueType = typename EnumeratorType::ValueType;
        template <typename TSelector>
        using KeyType = decltype(std::declval<TSelector>()(std::declval<ValueType>()));

        template <typename TSelector>
        auto DistinctBy(const TSelector selector) const -> Query<Enumerators::DistinctEnumerator<EnumeratorType, TSelector, Comparers::DefaultEqualityComparer<KeyType<TSelector>>>>;
        template <typename TSelector, typename TComparer>
        auto DistinctBy(const TSelector selector, const TComparer comparer) const -> Query<Enumerators::DistinctEnumerator<EnumeratorType, TSelector, TComparer>>;
    };
}