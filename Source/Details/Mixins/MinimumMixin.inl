#pragma once

#include "Details/Mixins/MinimumMixin.hpp"

#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Selectors/SelfSelector.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto MinimumMixin<TQuery>::Minimum() const -> ValueType
    {
        return MixinUtilities::GetQuery<TQuery>(*this).MinimumBy(Selectors::SelfSelector<ValueType>());
    }
}