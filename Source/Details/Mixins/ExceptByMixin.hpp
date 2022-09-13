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
        template <typename TSelector>
        using KeyType = decltype(std::declval<TSelector>()(std::declval<ValueType>()));

        template <typename TExceptEnumerator, typename TSelector>
        auto ExceptBy(const Query<TExceptEnumerator>& exceptQuery, const TSelector selector) const -> Query<Enumerators::ExceptEnumerator<EnumeratorType, TExceptEnumerator, TSelector, Comparers::DefaultEqualityComparer<KeyType<TSelector>>>>;
        template <typename TExceptEnumerator, typename TSelector, typename TComparer>
        auto ExceptBy(const Query<TExceptEnumerator>& exceptQuery, const TSelector selector, const TComparer comparer) const -> Query<Enumerators::ExceptEnumerator<EnumeratorType, TExceptEnumerator, TSelector, TComparer>>;
    };
}