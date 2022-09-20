#include "OrderBy/Sortable.hpp"

using namespace std;

namespace CppLinq::Tests::OrderBy
{
    auto Sortable::operator<(const Sortable right) const -> bool
    {
        ++comparisonCount;

        return value < right.value;
    }

    uint32_t Sortable::comparisonCount = 0U;
}