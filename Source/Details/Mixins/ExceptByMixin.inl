#pragma once

#include "Details/Mixins/ExceptByMixin.hpp"

#include "Details/Comparers/DefaultEqualityComparer.hpp"
#include "Details/Enumerators/ExceptEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TExceptEnumerator, typename TSelector>
    auto ExceptByMixin<TQuery>::ExceptBy(const Query<TExceptEnumerator>& exceptQuery, const TSelector selector) const -> Query<Enumerators::ExceptEnumerator<EnumeratorType, TExceptEnumerator, TSelector, Comparers::DefaultEqualityComparer<KeyType<TSelector>>>>
    {
        return ExceptBy(exceptQuery, selector, Comparers::DefaultEqualityComparer<KeyType<TSelector>>());
    }

    template <typename TQuery>
    template <typename TExceptEnumerator, typename TSelector, typename TComparer>
    auto ExceptByMixin<TQuery>::ExceptBy(const Query<TExceptEnumerator>& exceptQuery, const TSelector selector, const TComparer comparer) const -> Query<Enumerators::ExceptEnumerator<EnumeratorType, TExceptEnumerator, TSelector, TComparer>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), exceptQuery.GetEnumerator(), selector, comparer } };
    }
}