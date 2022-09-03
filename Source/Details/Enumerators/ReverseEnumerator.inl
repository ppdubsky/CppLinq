#pragma once

#include "Details/Enumerators/ReverseEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    ReverseEnumerator<TEnumerator>::ReverseEnumerator(const Query<TEnumerator>& query) :
        Base(query)
    {
    }
}