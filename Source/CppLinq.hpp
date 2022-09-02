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

    template <typename T, std::uint32_t TLength>
    auto From(const T (&array)[TLength]) -> Details::Query<Details::Enumerators::IteratorEnumerator<const T*>>
    {
        return { { reinterpret_cast<const T*>(&array), reinterpret_cast<const T*>(&array) + TLength } };
    }
}