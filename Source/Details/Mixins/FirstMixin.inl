#pragma once

#include "Details/Mixins/FirstMixin.hpp"

#include <optional>

#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Predicates/TruePredicate.hpp"
#include "Exceptions/EmptyContainerException.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto FirstMixin<TQuery>::First() const -> ValueType
    {
        return First(Predicates::TruePredicate<ValueType>());
    }

    template <typename TQuery>
    template <typename TPredicate>
    auto FirstMixin<TQuery>::First(const TPredicate predicate) const -> ValueType
    {
        const std::optional<ValueType> value = MixinUtilities::GetQuery<TQuery>(*this).FirstOptional(predicate);
        if (!value)
        {
            throw Exceptions::EmptyContainerException();
        }

        return *value;
    }
}