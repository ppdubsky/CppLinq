#include "OuterJoin/Person.hpp"

namespace CppLinq::Tests::OuterJoin
{
    auto Person::operator==(const Person& right) const -> bool
    {
        return name == right.name;
    }
}