#pragma once

#include "Details/Collections/DoNothingCollectionStrategy.hpp"

namespace CppLinq::Details::Collections
{
    template <typename TCollection>
    void DoNothingCollectionStrategy<TCollection>::PrepareCollection(const TCollection& /*collection*/)
    {
    }
}