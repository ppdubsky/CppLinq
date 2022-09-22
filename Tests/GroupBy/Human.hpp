#pragma once

#include <cstdint>
#include <string>

namespace CppLinq::Tests::GroupBy
{
    struct Human
    {
        auto operator==(const Human& right) const -> bool;

        std::uint32_t age;
        std::string name;
    };
}