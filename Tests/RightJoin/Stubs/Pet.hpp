#pragma once

#include <string>

#include "RightJoin/Stubs/Person.hpp"

namespace CppLinq::Tests::RightJoin::Stubs
{
    struct Pet final
    {
        auto operator==(const Pet& right) const -> bool;

        std::string name;
        Person owner;
    };
}