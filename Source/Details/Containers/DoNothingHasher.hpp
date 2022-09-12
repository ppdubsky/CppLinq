#pragma once

#include <cstdint>

namespace CppLinq::Details::Containers
{
    template <typename T>
    struct DoNothingHasher final
    {
        auto operator()(const T& value) const -> std::uint32_t;
    };
}