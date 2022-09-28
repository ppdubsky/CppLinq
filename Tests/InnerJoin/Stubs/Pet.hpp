#pragma once

#include <string>

#include "InnerJoin/Stubs/Person.hpp"

namespace CppLinq::Tests::InnerJoin::Stubs
{
    struct Pet final
    {
        auto operator==(const Pet& right) const -> bool;

        std::string name;
        Person owner;
    };
}