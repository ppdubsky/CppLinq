#include "UnionBy/Stubs/Customer.hpp"

namespace CppLinq::Tests::UnionBy::Stubs
{
    auto Customer::operator==(const Customer& right) const -> bool
    {
        return id == right.id && name == right.name;
    }
}