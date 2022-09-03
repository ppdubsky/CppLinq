#pragma once

namespace CppLinq::Details::Collections
{
    template <typename TCollection>
    struct SortCollectionStrategy final
    {
        static void PrepareCollection(TCollection& collection);
    };
}