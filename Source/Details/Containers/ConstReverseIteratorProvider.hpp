#pragma once

namespace CppLinq::Details::Containers
{
    template <typename TContainer>
    struct ConstReverseIteratorProvider final
    {
        using IteratorType = typename TContainer::const_reverse_iterator;

        static auto GetBegin(const TContainer& container) -> IteratorType;
        static auto GetEnd(const TContainer& container) -> IteratorType;
    };
}