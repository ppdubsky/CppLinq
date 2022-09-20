#include "UnionBy/Customer.hpp"

namespace CppLinq::Tests::UnionBy
{
    auto Customer::operator==(const Customer& right) const -> bool
    {
        return id == right.id && name == right.name;
    }
}