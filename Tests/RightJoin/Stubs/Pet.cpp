#include "RightJoin/Stubs/Pet.hpp"

namespace CppLinq::Tests::RightJoin::Stubs
{
    auto Pet::operator==(const Pet& right) const -> bool
    {
        return name == right.name && owner == right.owner;
    }
}