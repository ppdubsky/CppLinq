#pragma once

#include "Details/Enumerators/ContainerStrategies/SortContainerStrategy.hpp"

#include <algorithm>

namespace CppLinq::Details::Enumerators::ContainerStrategies
{
    template <typename TContainer>
    void SortContainerStrategy<TContainer>::PrepareContainer(TContainer& container)
    {
        std::sort(container.begin(), container.end());
    }
}