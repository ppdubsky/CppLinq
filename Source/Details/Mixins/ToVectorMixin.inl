#pragma once

#include "Details/Mixins/ToVectorMixin.hpp"

#include "Details/Mixins/MixinUtilities.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto ToVectorMixin<TQuery>::ToVector() const -> std::vector<ValueType>
    {
        std::vector<ValueType> items;

        EnumeratorType enumerator = MixinUtilities::GetEnumerator<TQuery>(*this);
        while (enumerator.HasCurrent())
        {
            items.push_back(enumerator.GetCurrent());

            enumerator.MoveNext();
        }

        return items;
    }
}