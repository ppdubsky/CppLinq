#include "LeftJoin/Stubs/Pet.hpp"

namespace CppLinq::Tests::LeftJoin::Stubs
{
    auto Pet::operator==(const Pet& right) const -> bool
    {
        return name == right.name && owner == right.owner;
    }
}