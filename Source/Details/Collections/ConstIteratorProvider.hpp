#pragma once

namespace CppLinq::Details::Collections
{
    template <typename TCollection>
    struct ConstIteratorProvider final
    {
        using IteratorType = typename TCollection::const_iterator;

        static auto GetBegin(const TCollection& collection) -> IteratorType;
        static auto GetEnd(const TCollection& collection) -> IteratorType;
    };
}