#pragma once

#include "Details/Mixins/FirstOrDefaultMixin.hpp"

#include "Details/Mixins/MixinUtilities.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto FirstOrDefaultMixin<TQuery>::FirstOrDefault() const -> ValueType
    {
        return FirstOrDefault(ValueType());
    }

    template <typename TQuery>
    auto FirstOrDefaultMixin<TQuery>::FirstOrDefault(const ValueType& defaultValue) const -> ValueType
    {
        return FirstOrDefault([](const ValueType /*value*/){ return true; }, defaultValue);
    }

    template <typename TQuery>
    template <typename TPredicate>
    auto FirstOrDefaultMixin<TQuery>::FirstOrDefault(const TPredicate predicate) const -> ValueType
    {
        return FirstOrDefault(predicate, ValueType());
    }

    template <typename TQuery>
    template <typename TPredicate>
    auto FirstOrDefaultMixin<TQuery>::FirstOrDefault(const TPredicate predicate, const ValueType& defaultValue) const -> ValueType
    {
        return MixinUtilities::GetQuery<TQuery>(*this).FirstOptional(predicate).value_or(defaultValue);
    }
}