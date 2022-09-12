#pragma once

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct ContainsMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        using ValueType = typename EnumeratorType::ValueType;

        auto Contains(const ValueType& value) const -> bool;
        template <typename TComparer>
        auto Contains(const ValueType& value, const TComparer comparer) const -> bool;
    };
}