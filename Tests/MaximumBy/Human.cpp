#include "MaximumBy/Human.hpp"

namespace CppLinq::Tests::MaximumBy
{
    auto Human::operator==(const Human& right) const -> bool
    {
        return age == right.age && name == right.name;
    }
}