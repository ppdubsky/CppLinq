#include "Intersect/Customer.hpp"

namespace CppLinq::Tests::Intersect
{
    auto Customer::operator==(const Customer& right) const -> bool
    {
        return id == right.id && name == right.name;
    }
}