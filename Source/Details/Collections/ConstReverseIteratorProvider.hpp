#pragma once

namespace CppLinq::Details::Collections
{
    template <typename TCollection>
    struct ConstReverseIteratorProvider final
    {
        using IteratorType = typename TCollection::const_reverse_iterator;

        static auto GetBegin(const TCollection& collection) -> IteratorType;
        static auto GetEnd(const TCollection& collection) -> IteratorType;
    };
}