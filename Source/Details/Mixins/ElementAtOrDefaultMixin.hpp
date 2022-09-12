#pragma once

#include <cstdint>

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct ElementAtOrDefaultMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        using ValueType = typename EnumeratorType::ValueType;

        auto ElementAtOrDefault(const std::uint32_t index) const -> ValueType;
        auto ElementAtOrDefault(const std::uint32_t index, const ValueType& defaultValue) const -> ValueType;
    };
}