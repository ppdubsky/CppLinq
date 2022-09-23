#pragma once

#include "Details/Comparers/DefaultEqualityComparer.Forward.hpp"
#include "Details/Enumerators/UnionEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"
#include "Details/Selectors/SelfSelector.Forward.hpp"

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct UnionMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        using ValueType = typename EnumeratorType::ValueType;

        template <typename TSecondEnumerator>
        auto Union(const Query<TSecondEnumerator>& secondQuery) const -> Query<Enumerators::UnionEnumerator<EnumeratorType, TSecondEnumerator, Selectors::SelfSelector<ValueType>, Comparers::DefaultEqualityComparer<ValueType>>>;
        template <typename TSecondEnumerator, typename TComparer>
        auto Union(const Query<TSecondEnumerator>& secondQuery, const TComparer comparer) const -> Query<Enumerators::UnionEnumerator<EnumeratorType, TSecondEnumerator, Selectors::SelfSelector<ValueType>, TComparer>>;
    };
}