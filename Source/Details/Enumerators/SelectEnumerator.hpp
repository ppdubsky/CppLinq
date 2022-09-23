#pragma once

#include "Details/Enumerators/SelectEnumerator.Forward.hpp"

#include <type_traits>

#include "Details/Enumerators/EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TResultSelector>
    struct SelectEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;
        using ValueType = decltype(std::declval<TResultSelector>()(std::declval<typename TEnumerator::ValueType>()));

        SelectEnumerator(const TEnumerator enumerator, const TResultSelector resultSelector);

        auto GetCurrent() -> ValueType;

    private:
        TResultSelector resultSelector;
    };
}