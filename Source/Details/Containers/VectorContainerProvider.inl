#pragma once

#include "Details/Containers/VectorContainerProvider.hpp"

#include "Details/Query.hpp"

namespace CppLinq::Details::Containers
{
    template <typename TEnumerator>
    auto VectorContainerProvider<TEnumerator>::GetContainer(const Query<TEnumerator>& query) -> ContainerType
    {
        return query.ToVector();
    }
}