#pragma once

#include "Details/Selectors/SelfSelector.Forward.hpp"

namespace CppLinq::Details::Selectors
{
    template <typename T>
    struct SelfSelector final
    {
        auto operator()(const T& value) const -> T;
    };
}