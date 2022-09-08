#pragma once

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct LastOrDefaultMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        using ValueType = typename EnumeratorType::ValueType;

        auto LastOrDefault() const -> ValueType;
        auto LastOrDefault(const ValueType& defaultValue) const -> ValueType;
        template <typename TPredicate>
        auto LastOrDefault(const TPredicate predicate) const -> ValueType;
        template <typename TPredicate>
        auto LastOrDefault(const TPredicate predicate, const ValueType& defaultValue) const -> ValueType;
    };
}