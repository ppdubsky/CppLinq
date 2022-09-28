#include "MinimumBy/Stubs/Human.hpp"

namespace CppLinq::Tests::MinimumBy::Stubs
{
    auto Human::operator==(const Human& right) const -> bool
    {
        return age == right.age && name == right.name;
    }
}