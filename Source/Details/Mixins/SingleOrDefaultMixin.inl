#pragma once

#include "Details/Mixins/SingleOrDefaultMixin.hpp"

#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Predicates/TruePredicate.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto SingleOrDefaultMixin<TQuery>::SingleOrDefault() const -> ValueType
    {
        return SingleOrDefault(ValueType());
    }

    template <typename TQuery>
    auto SingleOrDefaultMixin<TQuery>::SingleOrDefault(const ValueType& defaultValue) const -> ValueType
    {
        return SingleOrDefault(Predicates::TruePredicate<ValueType>(), defaultValue);
    }

    template <typename TQuery>
    template <typename TPredicate>
    auto SingleOrDefaultMixin<TQuery>::SingleOrDefault(const TPredicate predicate) const -> ValueType
    {
        return SingleOrDefault(predicate, ValueType());
    }

    template <typename TQuery>
    template <typename TPredicate>
    auto SingleOrDefaultMixin<TQuery>::SingleOrDefault(const TPredicate predicate, const ValueType& defaultValue) const -> ValueType
    {
        return MixinUtilities::GetQuery<TQuery>(*this).SingleOptional(predicate).value_or(defaultValue);
    }
}