#pragma once

#include "Details/Comparers/DefaultEqualityComparer.Forward.hpp"
#include "Details/Enumerators/ExceptEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include <type_traits>

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct ExceptByMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        using ValueType = typename EnumeratorType::ValueType;
        template <typename TKeySelector>
        using KeyType = decltype(std::declval<TKeySelector>()(std::declval<ValueType>()));

        template <typename TExceptEnumerator, typename TKeySelector>
        auto ExceptBy(const Query<TExceptEnumerator>& exceptQuery, const TKeySelector keySelector) const -> Query<Enumerators::ExceptEnumerator<EnumeratorType, TExceptEnumerator, TKeySelector, Comparers::DefaultEqualityComparer<KeyType<TKeySelector>>>>;
        template <typename TExceptEnumerator, typename TKeySelector, typename TKeyComparer>
        auto ExceptBy(const Query<TExceptEnumerator>& exceptQuery, const TKeySelector keySelector, const TKeyComparer keyComparer) const -> Query<Enumerators::ExceptEnumerator<EnumeratorType, TExceptEnumerator, TKeySelector, TKeyComparer>>;
    };
}