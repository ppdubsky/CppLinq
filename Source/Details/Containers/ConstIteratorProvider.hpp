#pragma once

namespace CppLinq::Details::Containers
{
    template <typename TContainer>
    struct ConstIteratorProvider final
    {
        using IteratorType = typename TContainer::const_iterator;

        static auto GetBegin(const TContainer& container) -> IteratorType;
        static auto GetEnd(const TContainer& container) -> IteratorType;
    };
}