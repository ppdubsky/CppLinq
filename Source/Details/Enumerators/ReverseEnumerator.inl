#pragma once

#include "Details/Enumerators/ReverseEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TContainer, typename TIterator>
    ReverseEnumerator<TContainer, TIterator>::ReverseEnumerator(const TContainer& container) :
        Base({ container.crbegin(), container.crend() }),
        container(container)
    {
    }
}