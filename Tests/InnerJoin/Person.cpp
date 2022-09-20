#include "InnerJoin/Person.hpp"

namespace CppLinq::Tests::InnerJoin
{
    auto Person::operator==(const Person& right) const -> bool
    {
        return name == right.name;
    }
}