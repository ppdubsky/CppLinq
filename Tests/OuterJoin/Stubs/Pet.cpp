#include "OuterJoin/Stubs/Pet.hpp"

namespace CppLinq::Tests::OuterJoin::Stubs
{
    auto Pet::operator==(const Pet& right) const -> bool
    {
        return name == right.name && owner == right.owner;
    }
}