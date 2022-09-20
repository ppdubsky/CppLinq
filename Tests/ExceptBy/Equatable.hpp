#pragma once

#include <cstdint>

namespace CppLinq::Tests::ExceptBy
{
    struct Equatable final
    {
        auto EqualTo(const Equatable other) const -> bool;
        auto operator==(const Equatable right) const -> bool;

        static std::uint32_t equalityCount;

        std::uint32_t value;
    };
}