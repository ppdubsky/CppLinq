#pragma once

#include "Details/Query.Forward.hpp"

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct SequenceEqualMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        using ValueType = typename EnumeratorType::ValueType;
        template <typename TOtherEnumerator>
        using OtherValueType = typename TOtherEnumerator::ValueType;

        template <typename TOtherEnumerator>
        auto SequenceEqual(const Query<TOtherEnumerator>& otherQuery) const -> bool;
        template <typename TOtherEnumerator, typename TComparer>
        auto SequenceEqual(const Query<TOtherEnumerator>& otherQuery, const TComparer comparer) const -> bool;
    };
}