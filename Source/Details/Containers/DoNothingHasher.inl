#pragma once

#include "Details/Containers/DoNothingHasher.hpp"

namespace CppLinq::Details::Containers
{
    template <typename T>
    auto DoNothingHasher<T>::operator()(const T& /*value*/) const -> std::uint32_t
    {
        return 0U;
    }
}