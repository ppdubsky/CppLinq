#pragma once

#include <cstdint>

namespace CppLinq::Tests::DistinctBy
{
    struct Equatable final
    {
        auto EqualTo(const Equatable other) const -> bool;
        auto operator==(const Equatable right) const -> bool;

        static uint32_t equalityCount;

        uint32_t value;
    };
}