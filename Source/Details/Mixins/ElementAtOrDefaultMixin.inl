#pragma once

#include "Details/Mixins/ElementAtOrDefaultMixin.hpp"

#include "Details/Mixins/MixinUtilities.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto ElementAtOrDefaultMixin<TQuery>::ElementAtOrDefault(const std::uint32_t index) const -> ValueType
    {
        return ElementAtOrDefault(index, ValueType());
    }

    template <typename TQuery>
    auto ElementAtOrDefaultMixin<TQuery>::ElementAtOrDefault(const std::uint32_t index, const ValueType& defaultValue) const -> ValueType
    {
        return MixinUtilities::GetQuery<TQuery>(*this).ElementAtOptional(index).value_or(defaultValue);
    }
}