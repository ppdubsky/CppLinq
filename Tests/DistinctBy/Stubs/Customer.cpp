#include "DistinctBy/Stubs/Customer.hpp"

namespace CppLinq::Tests::DistinctBy::Stubs
{
    auto Customer::operator==(const Customer& right) const -> bool
    {
        return id == right.id && name == right.name;
    }
}