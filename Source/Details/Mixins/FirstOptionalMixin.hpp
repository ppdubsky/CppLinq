#pragma once

#include <optional>

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct FirstOptionalMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        using ValueType = typename EnumeratorType::ValueType;

        auto FirstOptional() const -> std::optional<ValueType>;
        template <typename TPredicate>
        auto FirstOptional(const TPredicate predicate) const -> std::optional<ValueType>;
    };
}