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
    template <typename TExceptEnumerator, typename TKeySelector, typename TComparer>
    auto ExceptByMixin<TQuery>::ExceptBy(const Query<TExceptEnumerator>& exceptQuery, const TKeySelector keySelector, const TComparer comparer) const -> Query<Enumerators::ExceptEnumerator<EnumeratorType, TExceptEnumerator, TKeySelector, TComparer>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), exceptQuery.GetEnumerator(), keySelector, comparer } };
    }
}