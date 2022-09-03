#pragma once

#include "Details/Enumerators/IteratorProviders/ConstIteratorProvider.hpp"

namespace CppLinq::Details::Enumerators::IteratorProviders
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