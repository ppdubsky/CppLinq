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

        template <typename TUnionEnumerator>
        auto Union(const Query<TUnionEnumerator>& unionQuery) const -> Query<Enumerators::UnionEnumerator<EnumeratorType, TUnionEnumerator, Selectors::SelfSelector<ValueType>, Comparers::DefaultEqualityComparer<ValueType>>>;
        template <typename TUnionEnumerator, typename TComparer>
        auto Union(const Query<TUnionEnumerator>& unionQuery, const TComparer comparer) const -> Query<Enumerators::UnionEnumerator<EnumeratorType, TUnionEnumerator, Selectors::SelfSelector<ValueType>, TComparer>>;
    };
}