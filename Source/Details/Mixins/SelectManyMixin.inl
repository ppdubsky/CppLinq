#pragma once

#include "Details/Mixins/SelectManyMixin.hpp"

#include "Details/Enumerators/SelectManyEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TResultSelector>
    auto SelectManyMixin<TQuery>::SelectMany(const TResultSelector resultSelector) const -> Query<Enumerators::SelectManyEnumerator<EnumeratorType, TResultSelector>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), resultSelector } };
    }
}