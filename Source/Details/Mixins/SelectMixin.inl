#pragma once

#include "Details/Mixins/SelectMixin.hpp"

#include "Details/Enumerators/SelectEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TResultSelector>
    auto SelectMixin<TQuery>::Select(const TResultSelector resultSelector) const -> Query<Enumerators::SelectEnumerator<EnumeratorType, TResultSelector>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), resultSelector } };
    }
}