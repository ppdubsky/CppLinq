#pragma once

#include "Details/Containers/DoNothingContainerStrategy.hpp"

namespace CppLinq::Details::Containers
{
    template <typename TContainer>
    void DoNothingContainerStrategy<TContainer>::PrepareContainer(const TContainer& /*container*/)
    {
    }
}