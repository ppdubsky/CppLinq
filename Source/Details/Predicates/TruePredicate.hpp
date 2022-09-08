#pragma once

namespace CppLinq::Details::Predicates
{
    template <typename T>
    struct TruePredicate final
    {
        auto operator()(const T& value) const -> bool;
    };
}