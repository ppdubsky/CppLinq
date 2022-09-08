#pragma once

#include "Details/Mixins/SelectMixin.hpp"

#include "Details/Enumerators/SelectEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TSelector>
    auto SelectMixin<TQuery>::Select(const TSelector selector) const -> Query<Enumerators::SelectEnumerator<EnumeratorType, TSelector>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), selector } };
    }
}