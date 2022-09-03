#pragma once

namespace CppLinq::Details::Enumerators::ContainerStrategies
{
    template <typename TContainer>
    struct DoNothingContainerStrategy final
    {
        static void PrepareContainer(const TContainer& container);
    };
}