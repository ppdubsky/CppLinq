#pragma once

#include <type_traits>

#include "Details/Query.Forward.hpp"

namespace CppLinq::Details::Enumerators::ContainerProviders
{
    template <typename TEnumerator>
    struct VectorContainerProvider final
    {
        using ContainerType = decltype(std::declval<Query<TEnumerator>>().ToVector());

        static auto GetContainer(Query<TEnumerator>& query) -> ContainerType;
    };
}