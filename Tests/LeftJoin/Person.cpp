#include "LeftJoin/Person.hpp"

namespace CppLinq::Tests::LeftJoin
{
    auto Person::operator==(const Person& right) const -> bool
    {
        return name == right.name;
    }
}