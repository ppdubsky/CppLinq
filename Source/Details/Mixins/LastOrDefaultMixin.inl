#pragma once

#include "Details/Mixins/LastOrDefaultMixin.hpp"

#include "Details/Mixins/MixinUtilities.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto LastOrDefaultMixin<TQuery>::LastOrDefault() const -> ValueType
    {
        return LastOrDefault(ValueType());
    }

    template <typename TQuery>
    auto LastOrDefaultMixin<TQuery>::LastOrDefault(const ValueType& defaultValue) const -> ValueType
    {
        return LastOrDefault([](const ValueType /*value*/){ return true; }, defaultValue);
    }

    template <typename TQuery>
    template <typename TPredicate>
    auto LastOrDefaultMixin<TQuery>::LastOrDefault(const TPredicate predicate) const -> ValueType
    {
        return LastOrDefault(predicate, ValueType());
    }

    template <typename TQuery>
    template <typename TPredicate>
    auto LastOrDefaultMixin<TQuery>::LastOrDefault(const TPredicate predicate, const ValueType& defaultValue) const -> ValueType
    {
        return MixinUtilities::GetQuery<TQuery>(*this).LastOptional(predicate).value_or(defaultValue);
    }
}