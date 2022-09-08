#pragma once

#include "Details/Mixins/SingleMixin.hpp"

#include <optional>

#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Predicates/TruePredicate.hpp"
#include "Exceptions/EmptyContainerException.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto SingleMixin<TQuery>::Single() const -> ValueType
    {
        return Single(Predicates::TruePredicate<ValueType>());
    }

    template <typename TQuery>
    template <typename TPredicate>
    auto SingleMixin<TQuery>::Single(const TPredicate predicate) const -> ValueType
    {
        const std::optional<ValueType> value = MixinUtilities::GetQuery<TQuery>(*this).SingleOptional(predicate);
        if (!value)
        {
            throw Exceptions::EmptyContainerException();
        }

        return *value;
    }
}