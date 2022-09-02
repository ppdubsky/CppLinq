#pragma once

#include "Details/Enumerators/IteratorEnumerator.hpp"
#include "Details/Query.hpp"

namespace CppLinq
{
    template <typename TContainer>
    auto From(const TContainer& container) -> Details::Query<Details::Enumerators::IteratorEnumerator<typename TContainer::const_iterator>>
    {
        return { { container.cbegin(), container.cend() } };
    }

    template <typename T, int SIZE>
    auto From(const T (&array)[SIZE]) -> Details::Query<Details::Enumerators::IteratorEnumerator<const T*>>
    {
        return { { reinterpret_cast<const T*>(&array), reinterpret_cast<const T*>(&array) + SIZE } };
    }
}