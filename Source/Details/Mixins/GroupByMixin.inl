#pragma once

#include "Details/Mixins/GroupByMixin.hpp"

#include "Details/Comparers/DefaultEqualityComparer.hpp"
#include "Details/Enumerators/GroupEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TKeySelector, typename TElementSelector, typename TResultSelector>
    auto GroupByMixin<TQuery>::GroupBy(const TKeySelector keySelector, const TElementSelector elementSelector, const TResultSelector resultSelector) -> Query<Enumerators::GroupEnumerator<EnumeratorType, TKeySelector, TElementSelector, TResultSelector, Comparers::DefaultEqualityComparer<KeyType<TKeySelector>>>>
    {
        return GroupBy(keySelector, elementSelector, resultSelector, Comparers::DefaultEqualityComparer<KeyType<TKeySelector>>());
    }

    template <typename TQuery>
    template <typename TKeySelector, typename TElementSelector, typename TResultSelector, typename TKeyComparer>
    auto GroupByMixin<TQuery>::GroupBy(const TKeySelector keySelector, const TElementSelector elementSelector, const TResultSelector resultSelector, const TKeyComparer keyComparer) -> Query<Enumerators::GroupEnumerator<EnumeratorType, TKeySelector, TElementSelector, TResultSelector, TKeyComparer>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), keySelector, elementSelector, resultSelector, keyComparer } };
    }
}