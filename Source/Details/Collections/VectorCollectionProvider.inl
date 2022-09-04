#pragma once

#include "Details/Collections/VectorCollectionProvider.hpp"

#include "Details/Query.hpp"

namespace CppLinq::Details::Collections
{
    template <typename TEnumerator>
    auto VectorCollectionProvider<TEnumerator>::GetCollection(const Query<TEnumerator>& query) -> CollectionType
    {
        return query.ToVector();
    }
}