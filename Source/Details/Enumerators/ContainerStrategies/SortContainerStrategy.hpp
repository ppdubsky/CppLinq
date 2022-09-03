#pragma once

namespace CppLinq::Details::Enumerators::ContainerStrategies
{
    template <typename TContainer>
    struct SortContainerStrategy final
    {
        static void PrepareContainer(TContainer& container);
    };
}