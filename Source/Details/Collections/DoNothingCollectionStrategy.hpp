#pragma once

namespace CppLinq::Details::Collections
{
    template <typename TCollection>
    struct DoNothingCollectionStrategy final
    {
        static void PrepareCollection(const TCollection& collection);
    };
}