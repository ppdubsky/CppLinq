#pragma once

#include "Details/Containers/SortContainerStrategy.hpp"

#include <algorithm>

namespace CppLinq::Details::Containers
{
    template <typename TContainer>
    void SortContainerStrategy<TContainer>::PrepareContainer(TContainer& container)
    {
        std::sort(container.begin(), container.end());
    }
}