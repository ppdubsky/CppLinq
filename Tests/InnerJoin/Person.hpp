#pragma once

#include <string>

namespace CppLinq::Tests::InnerJoin
{
    struct Person final
    {
        auto operator==(const Person& right) const -> bool;

        std::string name;
    };
}