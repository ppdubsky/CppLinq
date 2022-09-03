#pragma once

#include "Details/Enumerators/OrderEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    OrderEnumerator<TEnumerator>::OrderEnumerator(const Query<TEnumerator>& query) :
        Base(query)
    {
    }
}