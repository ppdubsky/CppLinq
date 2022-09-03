#pragma once

#include "Details/Enumerators/IteratorProviders/ConstReverseIteratorProvider.hpp"

namespace CppLinq::Details::Enumerators::IteratorProviders
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