#pragma once

#include "Details/Enumerators/SelectManyEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct SelectManyMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;

        template <typename TSelector>
        auto SelectMany(const TSelector selector) const -> Query<Enumerators::SelectManyEnumerator<EnumeratorType, TSelector>>;
    };
}