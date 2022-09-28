#include "LeftJoin/Stubs/Person.hpp"

namespace CppLinq::Tests::LeftJoin::Stubs
{
    auto Person::operator==(const Person& right) const -> bool
    {
        return name == right.name;
    }
}