#pragma once

#include <type_traits>

#include "EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TSelector>
    struct SelectEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;
        using ValueType = decltype(std::declval<TSelector>()(std::declval<typename TEnumerator::ValueType>()));

        SelectEnumerator(const TEnumerator enumerator, const TSelector selector) :
            Base(enumerator),
            selector(selector)
        {
        }

        auto GetCurrent() -> ValueType
        {
            return selector(Base::GetCurrent());
        }

    private:
        TSelector selector;
    };
}