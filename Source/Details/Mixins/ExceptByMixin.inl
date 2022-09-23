#pragma once

#include "Details/Mixins/ExceptByMixin.hpp"

#include "Details/Comparers/DefaultEqualityComparer.hpp"
#include "Details/Enumerators/ExceptEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TSecondEnumerator, typename TKeySelector>
    auto ExceptByMixin<TQuery>::ExceptBy(const Query<TSecondEnumerator>& secondQuery, const TKeySelector keySelector) const -> Query<Enumerators::ExceptEnumerator<EnumeratorType, TSecondEnumerator, TKeySelector, Comparers::DefaultEqualityComparer<KeyType<TKeySelector>>>>
    {
        return ExceptBy(secondQuery, keySelector, Comparers::DefaultEqualityComparer<KeyType<TKeySelector>>());
    }

    template <typename TQuery>
    template <typename TSecondEnumerator, typename TKeySelector, typename TKeyComparer>
    auto ExceptByMixin<TQuery>::ExceptBy(const Query<TSecondEnumerator>& secondQuery, const TKeySelector keySelector, const TKeyComparer keyComparer) const -> Query<Enumerators::ExceptEnumerator<EnumeratorType, TSecondEnumerator, TKeySelector, TKeyComparer>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), secondQuery.GetEnumerator(), keySelector, keyComparer } };
    }
}