#include "InnerJoin/Stubs/Pet.hpp"

namespace CppLinq::Tests::InnerJoin::Stubs
{
    auto Pet::operator==(const Pet& right) const -> bool
    {
        return name == right.name && owner == right.owner;
    }
}