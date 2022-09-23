#pragma once

#include "Details/Comparers/DefaultEqualityComparer.Forward.hpp"
#include "Details/Enumerators/ExceptEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"
#include "Details/Selectors/SelfSelector.Forward.hpp"

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct ExceptMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        using ValueType = typename EnumeratorType::ValueType;

        template <typename TSecondEnumerator>
        auto Except(const Query<TSecondEnumerator>& secondQuery) const -> Query<Enumerators::ExceptEnumerator<EnumeratorType, TSecondEnumerator, Selectors::SelfSelector<ValueType>, Comparers::DefaultEqualityComparer<ValueType>>>;
        template <typename TSecondEnumerator, typename TComparer>
        auto Except(const Query<TSecondEnumerator>& secondQuery, const TComparer comparer) const -> Query<Enumerators::ExceptEnumerator<EnumeratorType, TSecondEnumerator, Selectors::SelfSelector<ValueType>, TComparer>>;
    };
}