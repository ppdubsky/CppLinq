#pragma once

#include "Details/Collections/ConstReverseIteratorProvider.hpp"

namespace CppLinq::Details::Collections
{
    template <typename TCollection>
    auto ConstReverseIteratorProvider<TCollection>::GetBegin(const TCollection& collection) -> IteratorType
    {
        return collection.crbegin();
    }

    template <typename TCollection>
    auto ConstReverseIteratorProvider<TCollection>::GetEnd(const TCollection& collection) -> IteratorType
    {
        return collection.crend();
    }
}