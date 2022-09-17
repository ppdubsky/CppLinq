#pragma once

#include "Details/Mixins/SelectManyMixin.hpp"

#include "Details/Enumerators/SelectManyEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TSelector>
    auto SelectManyMixin<TQuery>::SelectMany(const TSelector selector) const -> Query<Enumerators::SelectManyEnumerator<EnumeratorType, TSelector>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), selector } };
    }
}