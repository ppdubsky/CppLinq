#pragma once

#include "Details/Mixins/MaximumMixin.hpp"

#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Selectors/SelfSelector.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto MaximumMixin<TQuery>::Maximum() const -> ValueType
    {
        return MixinUtilities::GetQuery<TQuery>(*this).MaximumBy(Selectors::SelfSelector<ValueType>());
    }
}