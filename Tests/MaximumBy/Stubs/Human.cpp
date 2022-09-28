#include "MaximumBy/Stubs/Human.hpp"

namespace CppLinq::Tests::MaximumBy::Stubs
{
    auto Human::operator==(const Human& right) const -> bool
    {
        return age == right.age && name == right.name;
    }
}