#pragma once

namespace CppLinq::Details::Containers
{
    template <typename TContainer>
    struct DoNothingContainerStrategy final
    {
        static void PrepareContainer(const TContainer& container);
    };
}