#include "ExceptBy/Customer.hpp"

namespace CppLinq::Tests::ExceptBy
{
    auto Customer::operator==(const Customer& right) const -> bool
    {
        return id == right.id && name == right.name;
    }
}