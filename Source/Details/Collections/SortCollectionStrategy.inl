#pragma once

#include "Details/Collections/SortCollectionStrategy.hpp"

#include <algorithm>

namespace CppLinq::Details::Collections
{
    template <typename TCollection>
    void SortCollectionStrategy<TCollection>::PrepareCollection(TCollection& collection)
    {
        std::sort(collection.begin(), collection.end());
    }
}