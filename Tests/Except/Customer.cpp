#include "Except/Customer.hpp"

namespace CppLinq::Tests::Except
{
    auto Customer::operator==(const Customer& right) const -> bool
    {
        return id == right.id && name == right.name;
    }
}