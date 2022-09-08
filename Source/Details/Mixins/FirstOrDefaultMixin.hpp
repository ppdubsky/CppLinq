#pragma once

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct FirstOrDefaultMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        using ValueType = typename EnumeratorType::ValueType;

        auto FirstOrDefault() const -> ValueType;
        auto FirstOrDefault(const ValueType& defaultValue) const -> ValueType;
        template <typename TPredicate>
        auto FirstOrDefault(const TPredicate predicate) const -> ValueType;
        template <typename TPredicate>
        auto FirstOrDefault(const TPredicate predicate, const ValueType& defaultValue) const -> ValueType;
    };
}