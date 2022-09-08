#pragma once

#include <type_traits>

#include "Details/Query.Forward.hpp"

namespace CppLinq::Details::Containers
{
    template <typename TEnumerator>
    struct VectorContainerProvider final
    {
        using ContainerType = decltype(std::declval<Query<TEnumerator>>().ToVector());

        static auto GetContainer(const Query<TEnumerator>& query) -> ContainerType;
    };
}