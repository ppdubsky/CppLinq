#pragma once

#include "Details/Predicates/TruePredicate.hpp"

namespace CppLinq::Details::Predicates
{
    template <typename T>
    auto TruePredicate<T>::operator()(const T& /*value*/) const -> bool
    {
        return true;
    }
}