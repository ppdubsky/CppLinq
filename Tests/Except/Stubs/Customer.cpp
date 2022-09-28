#include "Except/Stubs/Customer.hpp"

namespace CppLinq::Tests::Except::Stubs
{
    auto Customer::operator==(const Customer& right) const -> bool
    {
        return id == right.id && name == right.name;
    }
}