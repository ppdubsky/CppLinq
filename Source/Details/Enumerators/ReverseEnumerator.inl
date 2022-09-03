#pragma once

#include "Details/Enumerators/ReverseEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TContainer>
    ReverseEnumerator<TContainer>::ReverseEnumerator(const TContainer& container) :
        Base({ container.crbegin(), container.crend() }),
        container(container)
    {
    }
}