#pragma once

#include "Details/Mixins/LastMixin.hpp"

#include <optional>

#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Predicates/TruePredicate.hpp"
#include "Exceptions/EmptyContainerException.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto LastMixin<TQuery>::Last() const -> ValueType
    {
        return Last(Predicates::TruePredicate<ValueType>());
    }

    template <typename TQuery>
    template <typename TPredicate>
    auto LastMixin<TQuery>::Last(const TPredicate predicate) const -> ValueType
    {
        const std::optional<ValueType> value = MixinUtilities::GetQuery<TQuery>(*this).LastOptional(predicate);
        if (!value)
        {
            throw Exceptions::EmptyContainerException();
        }

        return *value;
    }
}