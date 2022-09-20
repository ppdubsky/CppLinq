#pragma once

#include <cstdint>

namespace CppLinq::Tests::StaticCast
{
    struct ConvertibleToInt final
    {
        explicit operator int() const;

        static std::uint32_t castCount;
    };
}