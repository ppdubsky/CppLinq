#include "GroupBy/Human.hpp"

namespace CppLinq::Tests::GroupBy
{
    auto Human::operator==(const Human& right) const -> bool
    {
        return age == right.age && name == right.name;
    }
}