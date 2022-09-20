#pragma once

#include <cstdint>
#include <string>

namespace CppLinq::Tests::Except
{
    struct Customer final
    {
        auto operator==(const Customer& right) const -> bool;

        std::uint32_t id;
        std::string name;
    };
}