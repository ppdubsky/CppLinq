#pragma once

#include <cstdint>
#include <string>

namespace CppLinq::Tests::Select
{
    struct Customer final
    {
        std::uint32_t id;
        std::string name;
    };
}