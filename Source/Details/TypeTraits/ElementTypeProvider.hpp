#pragma once

#include <vector>

namespace CppLinq::Details::TypeTraits
{
    template <typename T>
    struct ElementTypeProvider;

    template <typename T>
    struct ElementTypeProvider<std::vector<T>> final
    {
        using ElementType = T;
    };
}