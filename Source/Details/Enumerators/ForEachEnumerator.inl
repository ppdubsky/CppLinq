#pragma once

#include "Details/Enumerators/ForEachEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TFunction>
    ForEachEnumerator<TEnumerator, TFunction>::ForEachEnumerator(const TEnumerator enumerator, const TFunction function) :
        Base(enumerator),
        function(function)
    {
    }

    template <typename TEnumerator, typename TFunction>
    auto ForEachEnumerator<TEnumerator, TFunction>::GetCurrent() -> Base::ValueType
    {
        const typename Base::ValueType value = Base::GetCurrent();

        function(value);

        return value;
    }
}