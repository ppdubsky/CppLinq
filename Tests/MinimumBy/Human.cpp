#include "MinimumBy/Human.hpp"

namespace CppLinq::Tests::MinimumBy
{
    auto Human::operator==(const Human& right) const -> bool
    {
        return age == right.age && name == right.name;
    }
}