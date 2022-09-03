#pragma once

#include "Details/Enumerators/ContainerProviders/VectorContainerProvider.hpp"

#include "Details/Query.hpp"

namespace CppLinq::Details::Enumerators::ContainerProviders
{
    template <typename TEnumerator>
    auto VectorContainerProvider<TEnumerator>::GetContainer(Query<TEnumerator>& query) -> ContainerType
    {
        return query.ToVector();
    }
}