#pragma once

#include "Details/Mixins/ElementAtMixin.hpp"

#include <optional>

#include "Details/Mixins/MixinUtilities.hpp"
#include "Exceptions/ArgumentOutOfRangeException.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto ElementAtMixin<TQuery>::ElementAt(const std::uint32_t index) const -> ValueType
    {
        const std::optional<ValueType> value = MixinUtilities::GetQuery<TQuery>(*this).ElementAtOptional(index);
        if (!value)
        {
            throw Exceptions::ArgumentOutOfRangeException();
        }

        return *value;
    }
}