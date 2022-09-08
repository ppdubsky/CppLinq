#pragma once

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct SumMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        using ValueType = typename EnumeratorType::ValueType;

        auto Sum() const -> ValueType;
    };
}