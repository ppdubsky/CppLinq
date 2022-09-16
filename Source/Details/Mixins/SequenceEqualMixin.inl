#pragma once

#include "Details/Mixins/SequenceEqualMixin.hpp"

#include "Details/Comparers/DefaultEqualityComparer.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TOtherEnumerator>
    auto SequenceEqualMixin<TQuery>::SequenceEqual(const Query<TOtherEnumerator>& otherQuery) const -> bool
    {
        return SequenceEqual(otherQuery, Comparers::DefaultEqualityComparer<ValueType, OtherValueType<TOtherEnumerator>>());
    }

    template <typename TQuery>
    template <typename TOtherEnumerator, typename TComparer>
    auto SequenceEqualMixin<TQuery>::SequenceEqual(const Query<TOtherEnumerator>& otherQuery, const TComparer comparer) const -> bool
    {
        auto areEqual = true;

        auto enumerator1 = MixinUtilities::GetEnumerator<TQuery>(*this);
        auto enumerator2 = otherQuery.GetEnumerator();

        while (enumerator1.HasCurrent() && enumerator2.HasCurrent())
        {
            if (!comparer(enumerator1.GetCurrent(), enumerator2.GetCurrent()))
            {
                areEqual = false;
                break;
            }

            enumerator1.MoveNext();
            enumerator2.MoveNext();
        }

        if (areEqual)
        {
            areEqual = enumerator1.HasCurrent() == enumerator2.HasCurrent();
        }

        return areEqual;
    }
}