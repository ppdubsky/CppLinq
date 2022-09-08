#pragma once

#include "Details/Containers/ConstReverseIteratorProvider.hpp"

namespace CppLinq::Details::Containers
{
    template <typename TContainer>
    auto ConstReverseIteratorProvider<TContainer>::GetBegin(const TContainer& container) -> IteratorType
    {
        return container.crbegin();
    }

    template <typename TContainer>
    auto ConstReverseIteratorProvider<TContainer>::GetEnd(const TContainer& container) -> IteratorType
    {
        return container.crend();
    }
}