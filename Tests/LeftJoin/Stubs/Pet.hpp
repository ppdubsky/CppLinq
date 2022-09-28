#pragma once

#include <string>

#include "LeftJoin/Stubs/Person.hpp"

namespace CppLinq::Tests::LeftJoin::Stubs
{
    struct Pet final
    {
        auto operator==(const Pet& right) const -> bool;

        std::string name;
        Person owner;
    };
}