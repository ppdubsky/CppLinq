#pragma once

#include <cstdint>
#include <vector>

namespace CppLinq::Tests::SelectMany
{
    struct Order final
    {
        std::uint32_t id;
        std::vector<int> items;
    };
}