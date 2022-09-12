#pragma once

#include <cstdint>
#include <optional>

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct ElementAtOptionalMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        using ValueType = typename EnumeratorType::ValueType;

        auto ElementAtOptional(const std::uint32_t index) const -> std::optional<ValueType>;
    };
}