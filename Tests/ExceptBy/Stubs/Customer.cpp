#include "ExceptBy/Stubs/Customer.hpp"

namespace CppLinq::Tests::ExceptBy::Stubs
{
    auto Customer::operator==(const Customer& right) const -> bool
    {
        return id == right.id && name == right.name;
    }
}