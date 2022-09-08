#pragma once

#include "Details/Enumerators/SelectEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct SelectMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;

        template <typename TSelector>
        auto Select(const TSelector selector) const -> Query<Enumerators::SelectEnumerator<EnumeratorType, TSelector>>;
    };
}