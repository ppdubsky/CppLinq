#pragma once

#include "Details/Selectors/SelfSelector.hpp"

namespace CppLinq::Details::Selectors
{
    template <typename T>
    auto SelfSelector<T>::operator()(const T& value) const -> T
    {
        return value;
    }
}