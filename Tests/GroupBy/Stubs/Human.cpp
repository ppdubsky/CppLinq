#include "GroupBy/Stubs/Human.hpp"

namespace CppLinq::Tests::GroupBy::Stubs
{
    auto Human::operator==(const Human& right) const -> bool
    {
        return age == right.age && name == right.name;
    }
}