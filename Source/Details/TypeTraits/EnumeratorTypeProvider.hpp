#pragma once

#include "Details/Query.Forward.hpp"

namespace CppLinq::Details::TypeTraits
{
    template <typename T>
    struct EnumeratorTypeProvider;

    template <typename TEnumerator>
    struct EnumeratorTypeProvider<Query<TEnumerator>> final
    {
        using EnumeratorType = TEnumerator;
    };
}