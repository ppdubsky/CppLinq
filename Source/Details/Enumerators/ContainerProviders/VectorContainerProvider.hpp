#pragma once

#include <type_traits>

namespace CppLinq::Details
{
    template <typename TEnumerator>
    struct Query;
}

namespace CppLinq::Details::Enumerators::ContainerProviders
{
    template <typename TEnumerator>
    struct VectorContainerProvider final
    {
        using ContainerType = decltype(std::declval<Query<TEnumerator>>().ToVector());

        static auto GetContainer(Query<TEnumerator>& query) -> ContainerType;
    };
}