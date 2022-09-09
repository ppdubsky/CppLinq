#pragma once

#include "Details/Mixins/DistinctMixin.hpp"

#include "Details/Comparers/DefaultEqualityComparer.hpp"
#include "Details/Enumerators/DistinctEnumerator.hpp"
#include "Details/Mixins/ContainsMixin.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto DistinctMixin<TQuery>::Distinct() const -> Query<Enumerators::DistinctEnumerator<EnumeratorType, Comparers::DefaultEqualityComparer<ValueType>>>
    {
        return Distinct(Comparers::DefaultEqualityComparer<ValueType>());
    }

    template <typename TQuery>
    template <typename TComparer>
    auto DistinctMixin<TQuery>::Distinct(const TComparer comparer) const -> Query<Enumerators::DistinctEnumerator<EnumeratorType, TComparer>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), comparer } };
    }
}