#pragma once

#include "Details/Mixins/DistinctMixin.hpp"

#include "Details/Comparers/DefaultEqualityComparer.hpp"
#include "Details/Enumerators/DistinctEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"
#include "Details/Selectors/SelfSelector.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto DistinctMixin<TQuery>::Distinct() const -> Query<Enumerators::DistinctEnumerator<EnumeratorType, Selectors::SelfSelector<ValueType>, Comparers::DefaultEqualityComparer<ValueType>>>
    {
        return Distinct(Comparers::DefaultEqualityComparer<ValueType>());
    }

    template <typename TQuery>
    template <typename TComparer>
    auto DistinctMixin<TQuery>::Distinct(const TComparer comparer) const -> Query<Enumerators::DistinctEnumerator<EnumeratorType, Selectors::SelfSelector<ValueType>, TComparer>>
    {
        return MixinUtilities::GetQuery<TQuery>(*this).DistinctBy(Selectors::SelfSelector<ValueType>(), comparer);
    }
}