#pragma once

#include <string>

#include "OuterJoin/Person.hpp"

namespace CppLinq::Tests::OuterJoin
{
    struct Pet final
    {
        auto operator==(const Pet& right) const -> bool;

        std::string name;
        Person owner;
    };
}