#pragma once

#include "Details/Mixins/SumMixin.hpp"

#include "Details/Mixins/MixinUtilities.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto SumMixin<TQuery>::Sum() const -> ValueType
    {
        auto sum = static_cast<ValueType>(0);

        EnumeratorType enumerator = MixinUtilities::GetEnumerator<TQuery>(*this);
        while (enumerator.HasCurrent())
        {
            sum += enumerator.GetCurrent();

            enumerator.MoveNext();
        }

        return sum;
    }
}