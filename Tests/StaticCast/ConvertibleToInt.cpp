#include "StaticCast/ConvertibleToInt.hpp"

namespace CppLinq::Tests::StaticCast
{
    ConvertibleToInt::operator int() const
    {
        ++castCount;

        return 0;
    }

    std::uint32_t ConvertibleToInt::castCount = 0U;
}