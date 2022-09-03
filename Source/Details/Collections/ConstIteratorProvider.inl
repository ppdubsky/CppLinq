#pragma once

#include "Details/Collections/ConstIteratorProvider.hpp"

namespace CppLinq::Details::Collections
{
    template <typename TCollection>
    auto ConstIteratorProvider<TCollection>::GetBegin(const TCollection& collection) -> IteratorType
    {
        return collection.cbegin();
    }

    template <typename TCollection>
    auto ConstIteratorProvider<TCollection>::GetEnd(const TCollection& collection) -> IteratorType
    {
        return collection.cend();
    }
}