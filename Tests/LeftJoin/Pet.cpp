#include "LeftJoin/Pet.hpp"

namespace CppLinq::Tests::LeftJoin
{
    auto Pet::operator==(const Pet& right) const -> bool
    {
        return name == right.name && owner == right.owner;
    }
}