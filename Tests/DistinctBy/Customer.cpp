#include "DistinctBy/Customer.hpp"

namespace CppLinq::Tests::DistinctBy
{
    auto Customer::operator==(const Customer& right) const -> bool
    {
        return id == right.id && name == right.name;
    }
}