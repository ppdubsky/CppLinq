#pragma once

#include "Details/Mixins/ElementAtOptionalMixin.hpp"

#include "Details/Mixins/MixinUtilities.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto ElementAtOptionalMixin<TQuery>::ElementAtOptional(const std::uint32_t index) const -> std::optional<ValueType>
    {
        std::optional<ValueType> element;

        auto currentIndex = 0U;

        for (const ValueType& value : MixinUtilities::GetQuery<TQuery>(*this))
        {
            if (currentIndex == index)
            {
                element = value;
                break;
            }

            ++currentIndex;
        }

        return element;
    }
}