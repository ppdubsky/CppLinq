#pragma once

#include "Details/Comparers/DefaultEqualityComparer.Forward.hpp"

namespace CppLinq::Details::Comparers
{
    template <typename T>
    struct DefaultEqualityComparer final
    {
        auto operator()(const T& value1, const T& value2) const -> bool;
    };
}