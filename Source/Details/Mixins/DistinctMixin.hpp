#pragma once

#include "Details/Comparers/DefaultEqualityComparer.Forward.hpp"
#include "Details/Enumerators/DistinctEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"
#include "Details/Selectors/SelfSelector.Forward.hpp"

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct DistinctMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        using ValueType = typename EnumeratorType::ValueType;

        auto Distinct() const -> Query<Enumerators::DistinctEnumerator<EnumeratorType, Selectors::SelfSelector<ValueType>, Comparers::DefaultEqualityComparer<ValueType>>>;
        template <typename TComparer>
        auto Distinct(const TComparer comparer) const -> Query<Enumerators::DistinctEnumerator<EnumeratorType, Selectors::SelfSelector<ValueType>, TComparer>>;
    };
}