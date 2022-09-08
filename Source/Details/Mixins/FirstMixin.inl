#pragma once

#include "Details/Mixins/FirstMixin.hpp"

#include <optional>

#include "Details/Mixins/MixinUtilities.hpp"
#include "Exceptions/EmptyCollectionException.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto FirstMixin<TQuery>::First() const -> ValueType
    {
        return First([](const ValueType& /*value*/){ return true; });
    }

    template <typename TQuery>
    template <typename TPredicate>
    auto FirstMixin<TQuery>::First(const TPredicate predicate) const -> ValueType
    {
        const std::optional<ValueType> value = MixinUtilities::GetQuery<TQuery>(*this).FirstOptional(predicate);
        if (!value)
        {
            throw Exceptions::EmptyCollectionException();
        }

        return *value;
    }
}