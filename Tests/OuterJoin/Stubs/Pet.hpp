#pragma once

#include <string>

#include "OuterJoin/Stubs/Person.hpp"

namespace CppLinq::Tests::OuterJoin::Stubs
{
    struct Pet final
    {
        auto operator==(const Pet& right) const -> bool;

        std::string name;
        Person owner;
    };
}