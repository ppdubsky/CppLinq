#pragma once

#include <string>

#include "RightJoin/Person.hpp"

namespace CppLinq::Tests::RightJoin
{
    struct Pet final
    {
        auto operator==(const Pet& right) const -> bool;

        std::string name;
        Person owner;
    };
}