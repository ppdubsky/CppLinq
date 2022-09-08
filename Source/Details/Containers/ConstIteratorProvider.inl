#pragma once

#include "Details/Containers/ConstIteratorProvider.hpp"

namespace CppLinq::Details::Containers
{
    template <typename TContainer>
    auto ConstIteratorProvider<TContainer>::GetBegin(const TContainer& container) -> IteratorType
    {
        return container.cbegin();
    }

    template <typename TContainer>
    auto ConstIteratorProvider<TContainer>::GetEnd(const TContainer& container) -> IteratorType
    {
        return container.cend();
    }
}