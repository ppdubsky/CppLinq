#pragma once

#include <cstdint>

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct CountMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        using ValueType = typename EnumeratorType::ValueType;

        auto Count() const -> std::uint32_t;
        template <typename TPredicate>
        auto Count(const TPredicate predicate) const -> std::uint32_t;
    };
}