#include "IntersectBy/Stubs/Customer.hpp"

namespace CppLinq::Tests::IntersectBy::Stubs
{
    auto Customer::operator==(const Customer& right) const -> bool
    {
        return id == right.id && name == right.name;
    }
}