#pragma once

namespace CppLinq::Details::Containers
{
    template <typename TContainer>
    struct SortContainerStrategy final
    {
        static void PrepareContainer(TContainer& container);
    };
}