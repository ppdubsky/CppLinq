#include "OuterJoin/Pet.hpp"

namespace CppLinq::Tests::OuterJoin
{
    auto Pet::operator==(const Pet& right) const -> bool
    {
        return name == right.name && owner == right.owner;
    }
}