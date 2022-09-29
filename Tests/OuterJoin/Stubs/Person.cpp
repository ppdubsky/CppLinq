#include "OuterJoin/Stubs/Person.hpp"

namespace CppLinq::Tests::OuterJoin::Stubs
{
    auto Person::operator==(const Person& right) const -> bool
    {
        return name == right.name;
    }
}