#pragma once

#include <cstdint>

namespace CppLinq::Details::Storage
{
    template <typename T>
    struct IndexedValue final
    {
        std::int32_t index{ -1 };
        T value;
    };
}