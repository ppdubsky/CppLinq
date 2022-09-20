#pragma once

#include <string>

#include "InnerJoin/Person.hpp"

namespace CppLinq::Tests::InnerJoin
{
    struct Pet final
    {
        auto operator==(const Pet& right) const -> bool;

        std::string name;
        Person owner;
    };
}