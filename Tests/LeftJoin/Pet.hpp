#pragma once

#include <string>

#include "LeftJoin/Person.hpp"

namespace CppLinq::Tests::LeftJoin
{
    struct Pet final
    {
        auto operator==(const Pet& right) const -> bool;

        std::string name;
        Person owner;
    };
}