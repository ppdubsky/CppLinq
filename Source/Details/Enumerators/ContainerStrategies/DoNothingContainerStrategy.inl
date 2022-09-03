#pragma once

#include "Details/Enumerators/ContainerStrategies/DoNothingContainerStrategy.hpp"

namespace CppLinq::Details::Enumerators::ContainerStrategies
{
    template <typename TContainer>
    void DoNothingContainerStrategy<TContainer>::PrepareContainer(const TContainer& /*container*/)
    {
    }
}