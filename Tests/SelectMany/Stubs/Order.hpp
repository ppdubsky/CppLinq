#pragma once

#include <cstdint>
#include <vector>

namespace CppLinq::Tests::SelectMany::Stubs
{
    struct Order final
    {
        std::uint32_t id;
        std::vector<int> items;
    };
}