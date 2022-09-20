#pragma once

#include <cstdint>

namespace CppLinq::Tests::OrderBy
{
    struct Sortable final
    {
        auto operator<(const Sortable right) const -> bool;

        static std::uint32_t comparisonCount;

        std::uint32_t value;
    };
}