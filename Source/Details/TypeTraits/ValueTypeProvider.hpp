#pragma once

#include <type_traits>

namespace CppLinq::Details::TypeTraits
{
    template <typename TIterator>
    struct ValueTypeProvider final
    {
        using ValueType = typename TIterator::value_type;
    };

    template <typename T>
    struct ValueTypeProvider<T*> final
    {
        using ValueType = std::remove_cv_t<T>;
    };
}