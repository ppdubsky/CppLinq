#pragma once

#include <type_traits>

namespace CppLinq::Details::TypeTraits
{
    template <typename TFunction, typename... TArguments>
    struct FunctionReturnTypeProvider final
    {
        using ReturnType = decltype(std::declval<TFunction>()(std::declval<TArguments>()...));
    };
}