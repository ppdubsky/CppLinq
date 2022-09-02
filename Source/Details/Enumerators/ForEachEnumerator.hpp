#pragma once

#include "EnumeratorWrapper.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, typename TFunction>
    struct ForEachEnumerator final : EnumeratorWrapper<TEnumerator>
    {
        using Base = EnumeratorWrapper<TEnumerator>;

        ForEachEnumerator(const TEnumerator enumerator, const TFunction function) :
            Base(enumerator),
            function(function)
        {
        }

        auto GetCurrent() -> Base::ValueType
        {
            const Base::ValueType value = Base::GetCurrent();

            function(value);

            return value;
        }

    private:
        TFunction function;
    };
}