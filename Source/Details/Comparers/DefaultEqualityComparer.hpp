#pragma once

#include "Details/Comparers/DefaultEqualityComparer.Forward.hpp"

namespace CppLinq::Details::Comparers
{
    template <typename T1, typename T2>
    struct DefaultEqualityComparer final
    {
        auto operator()(const T1& value1, const T2& value2) const -> bool;
    };
}