#pragma once

#include "Details/Mixins/DistinctByMixin.hpp"

#include "Details/Comparers/DefaultEqualityComparer.hpp"
#include "Details/Enumerators/DistinctEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TSelector>
    auto DistinctByMixin<TQuery>::DistinctBy(const TSelector selector) const -> Query<Enumerators::DistinctEnumerator<EnumeratorType, TSelector, Comparers::DefaultEqualityComparer<KeyType<TSelector>>>>
    {
        return DistinctBy(selector, Comparers::DefaultEqualityComparer<KeyType<TSelector>>());
    }

    template <typename TQuery>
    template <typename TSelector, typename TComparer>
    auto DistinctByMixin<TQuery>::DistinctBy(const TSelector selector, const TComparer comparer) const -> Query<Enumerators::DistinctEnumerator<EnumeratorType, TSelector, TComparer>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), selector, comparer } };
    }
}