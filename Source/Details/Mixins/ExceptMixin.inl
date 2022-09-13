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
    template <typename TExceptEnumerator>
    auto ExceptMixin<TQuery>::Except(const Query<TExceptEnumerator>& exceptQuery) const -> Query<Enumerators::ExceptEnumerator<EnumeratorType, TExceptEnumerator, Selectors::SelfSelector<ValueType>, Comparers::DefaultEqualityComparer<ValueType>>>
    {
        return Except(exceptQuery, Comparers::DefaultEqualityComparer<ValueType>());
    }

    template <typename TQuery>
    template <typename TExceptEnumerator, typename TComparer>
    auto ExceptMixin<TQuery>::Except(const Query<TExceptEnumerator>& exceptQuery, const TComparer comparer) const -> Query<Enumerators::ExceptEnumerator<EnumeratorType, TExceptEnumerator, Selectors::SelfSelector<ValueType>, TComparer>>
    {
        return MixinUtilities::GetQuery<TQuery>(*this).ExceptBy(exceptQuery, Selectors::SelfSelector<ValueType>(), comparer);
    }
}