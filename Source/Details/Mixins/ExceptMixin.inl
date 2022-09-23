#pragma once

#include "Details/Mixins/ExceptMixin.hpp"

#include "Details/Comparers/DefaultEqualityComparer.hpp"
#include "Details/Enumerators/ExceptEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"
#include "Details/Selectors/SelfSelector.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TSecondEnumerator>
    auto ExceptMixin<TQuery>::Except(const Query<TSecondEnumerator>& secondQuery) const -> Query<Enumerators::ExceptEnumerator<EnumeratorType, TSecondEnumerator, Selectors::SelfSelector<ValueType>, Comparers::DefaultEqualityComparer<ValueType>>>
    {
        return Except(secondQuery, Comparers::DefaultEqualityComparer<ValueType>());
    }

    template <typename TQuery>
    template <typename TSecondEnumerator, typename TComparer>
    auto ExceptMixin<TQuery>::Except(const Query<TSecondEnumerator>& secondQuery, const TComparer comparer) const -> Query<Enumerators::ExceptEnumerator<EnumeratorType, TSecondEnumerator, Selectors::SelfSelector<ValueType>, TComparer>>
    {
        return MixinUtilities::GetQuery<TQuery>(*this).ExceptBy(secondQuery, Selectors::SelfSelector<ValueType>(), comparer);
    }
}