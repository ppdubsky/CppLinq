#pragma once

#include "Details/Comparers/DefaultEqualityComparer.Forward.hpp"
#include "Details/Enumerators/DistinctEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include "Details/Mixins/MixinUtilities.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct DistinctMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        using ValueType = typename EnumeratorType::ValueType;

        auto Distinct() const -> Query<Enumerators::DistinctEnumerator<EnumeratorType, Comparers::DefaultEqualityComparer<ValueType>>>;
        template <typename TComparer>
        auto Distinct(const TComparer comparer) const -> Query<Enumerators::DistinctEnumerator<EnumeratorType, TComparer>>;
    };
}