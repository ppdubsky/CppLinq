#pragma once

#include <optional>

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct SingleOptionalMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        using ValueType = typename EnumeratorType::ValueType;

        auto SingleOptional() const -> std::optional<ValueType>;
        template <typename TPredicate>
        auto SingleOptional(const TPredicate predicate) const -> std::optional<ValueType>;
    };
}