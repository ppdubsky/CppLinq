#pragma once

#include "Details/Mixins/DistinctByMixin.hpp"

#include "Details/Comparers/DefaultEqualityComparer.hpp"
#include "Details/Enumerators/DistinctEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TKeySelector>
    auto DistinctByMixin<TQuery>::DistinctBy(const TKeySelector keySelector) const -> Query<Enumerators::DistinctEnumerator<EnumeratorType, TKeySelector, Comparers::DefaultEqualityComparer<KeyType<TKeySelector>>>>
    {
        return DistinctBy(keySelector, Comparers::DefaultEqualityComparer<KeyType<TKeySelector>>());
    }

    template <typename TQuery>
    template <typename TKeySelector, typename TKeyComparer>
    auto DistinctByMixin<TQuery>::DistinctBy(const TKeySelector keySelector, const TKeyComparer keyComparer) const -> Query<Enumerators::DistinctEnumerator<EnumeratorType, TKeySelector, TKeyComparer>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), keySelector, keyComparer } };
    }
}