#include "RightJoin/Pet.hpp"

namespace CppLinq::Tests::RightJoin
{
    auto Pet::operator==(const Pet& right) const -> bool
    {
        return name == right.name && owner == right.owner;
    }
}