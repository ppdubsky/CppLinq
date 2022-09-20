#include "IntersectBy/Customer.hpp"

namespace CppLinq::Tests::IntersectBy
{
    auto Customer::operator==(const Customer& right) const -> bool
    {
        return id == right.id && name == right.name;
    }
}