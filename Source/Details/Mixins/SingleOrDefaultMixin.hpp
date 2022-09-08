#pragma once

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct SingleOrDefaultMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        using ValueType = typename EnumeratorType::ValueType;

        auto SingleOrDefault() const -> ValueType;
        auto SingleOrDefault(const ValueType& defaultValue) const -> ValueType;
        template <typename TPredicate>
        auto SingleOrDefault(const TPredicate predicate) const -> ValueType;
        template <typename TPredicate>
        auto SingleOrDefault(const TPredicate predicate, const ValueType& defaultValue) const -> ValueType;
    };
}