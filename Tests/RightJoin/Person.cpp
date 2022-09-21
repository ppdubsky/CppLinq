#include "RightJoin/Person.hpp"

namespace CppLinq::Tests::RightJoin
{
    auto Person::operator==(const Person& right) const -> bool
    {
        return name == right.name;
    }
}