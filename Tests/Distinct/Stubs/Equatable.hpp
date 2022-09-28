#pragma once

#include <cstdint>

namespace CppLinq::Tests::Distinct::Stubs
{
    struct Equatable final
    {
        auto EqualTo(const Equatable other) const -> bool;
        auto operator==(const Equatable right) const -> bool;

        static std::uint32_t equalityCount;

        std::uint32_t value;
    };
}