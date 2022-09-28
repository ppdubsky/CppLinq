#include "InnerJoin/Stubs/Person.hpp"

namespace CppLinq::Tests::InnerJoin::Stubs
{
    auto Person::operator==(const Person& right) const -> bool
    {
        return name == right.name;
    }
}