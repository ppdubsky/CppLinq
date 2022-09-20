#include "InnerJoin/Pet.hpp"

namespace CppLinq::Tests::InnerJoin
{
    auto Pet::operator==(const Pet& right) const -> bool
    {
        return name == right.name && owner == right.owner;
    }
}