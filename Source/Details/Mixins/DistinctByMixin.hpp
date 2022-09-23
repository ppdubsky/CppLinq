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
        template <typename TKeySelector>
        using KeyType = decltype(std::declval<TKeySelector>()(std::declval<ValueType>()));

        template <typename TKeySelector>
        auto DistinctBy(const TKeySelector keySelector) const -> Query<Enumerators::DistinctEnumerator<EnumeratorType, TKeySelector, Comparers::DefaultEqualityComparer<KeyType<TKeySelector>>>>;
        template <typename TKeySelector, typename TKeyComparer>
        auto DistinctBy(const TKeySelector keySelector, const TKeyComparer keyComparer) const -> Query<Enumerators::DistinctEnumerator<EnumeratorType, TKeySelector, TKeyComparer>>;
    };
}