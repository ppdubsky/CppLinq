#pragma once

#include "Details/Mixins/ContainsMixin.hpp"

#include "Details/Mixins/MixinUtilities.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto ContainsMixin<TQuery>::Contains(const ValueType& value) const -> bool
    {
        return Contains(value, [](const ValueType& object1, const ValueType& object2){ return object1 == object2; });
    }
    
    template <typename TQuery>
    template <typename TComparer>
    auto ContainsMixin<TQuery>::Contains(const ValueType& value, const TComparer comparer) const -> bool
    {
        auto contains = false;

        for (const ValueType& existingValue : MixinUtilities::GetQuery<TQuery>(*this))
        {
            if (comparer(existingValue, value))
            {
                contains = true;
                break;
            }
        }

        return contains;
    }
}