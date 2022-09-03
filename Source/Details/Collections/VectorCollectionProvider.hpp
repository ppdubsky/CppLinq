#pragma once

#include <type_traits>

#include "Details/Query.Forward.hpp"

namespace CppLinq::Details::Collections
{
    template <typename TEnumerator>
    struct VectorCollectionProvider final
    {
        using CollectionType = decltype(std::declval<Query<TEnumerator>>().ToVector());

        static auto GetCollection(Query<TEnumerator>& query) -> CollectionType;
    };
}