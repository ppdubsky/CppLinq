#pragma once

#include "Details/Mixins/ExceptByMixin.hpp"

#include "Details/Comparers/DefaultEqualityComparer.hpp"
#include "Details/Enumerators/ExceptEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TExceptEnumerator, typename TKeySelector>
    auto ExceptByMixin<TQuery>::ExceptBy(const Query<TExceptEnumerator>& exceptQuery, const TKeySelector keySelector) const -> Query<Enumerators::ExceptEnumerator<EnumeratorType, TExceptEnumerator, TKeySelector, Comparers::DefaultEqualityComparer<KeyType<TKeySelector>>>>
    {
        return ExceptBy(exceptQuery, keySelector, Comparers::DefaultEqualityComparer<KeyType<TKeySelector>>());
    }

    template <typename TQuery>
    template <typename TExceptEnumerator, typename TKeySelector, typename TKeyComparer>
    auto ExceptByMixin<TQuery>::ExceptBy(const Query<TExceptEnumerator>& exceptQuery, const TKeySelector keySelector, const TKeyComparer keyComparer) const -> Query<Enumerators::ExceptEnumerator<EnumeratorType, TExceptEnumerator, TKeySelector, TKeyComparer>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), exceptQuery.GetEnumerator(), keySelector, keyComparer } };
    }
}