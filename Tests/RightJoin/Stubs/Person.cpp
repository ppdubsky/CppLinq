#include "RightJoin/Stubs/Person.hpp"

namespace CppLinq::Tests::RightJoin::Stubs
{
    auto Person::operator==(const Person& right) const -> bool
    {
        return name == right.name;
    }
}