#pragma once

#include "Details/Comparers/DefaultEqualityComparer.hpp"

namespace CppLinq::Details::Comparers
{
    template <typename T>
    auto DefaultEqualityComparer<T>::operator()(const T& value1, const T& value2) const -> bool
    {
        return value1 == value2;
    }
}