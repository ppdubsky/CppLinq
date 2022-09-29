#pragma once

#include <string>

namespace CppLinq::Tests::RightJoin::Stubs
{
    struct Person final
    {
        auto operator==(const Person& right) const -> bool;

        std::string name;
    };
}