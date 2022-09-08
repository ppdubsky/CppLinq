#pragma once

#include <optional>

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct LastOptionalMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        using ValueType = typename EnumeratorType::ValueType;

        auto LastOptional() const -> std::optional<ValueType>;
        template <typename TPredicate>
        auto LastOptional(const TPredicate predicate) const -> std::optional<ValueType>;
    };
}