#include "IntersectBy/Equatable.hpp"

namespace CppLinq::Tests::IntersectBy
{
    auto Equatable::EqualTo(const Equatable other) const -> bool
    {
        ++equalityCount;

        return value == other.value;
    }

    auto Equatable::operator==(const Equatable right) const -> bool
    {
        return EqualTo(right);
    }

    uint32_t Equatable::equalityCount = 0U;
}