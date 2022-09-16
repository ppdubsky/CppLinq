#pragma once

#include "Details/Comparers/DefaultEqualityComparer.hpp"

namespace CppLinq::Details::Comparers
{
    template <typename T1, typename T2>
    auto DefaultEqualityComparer<T1, T2>::operator()(const T1& value1, const T2& value2) const -> bool
    {
        return value1 == value2;
    }
}