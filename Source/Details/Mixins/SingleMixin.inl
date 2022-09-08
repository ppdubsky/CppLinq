#pragma once

#include "Details/Mixins/SingleMixin.hpp"

#include <optional>

#include "Details/Mixins/MixinUtilities.hpp"
#include "Exceptions/EmptyCollectionException.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto SingleMixin<TQuery>::Single() const -> ValueType
    {
        return Single([](const ValueType& /*value*/){ return true; });
    }

    template <typename TQuery>
    template <typename TPredicate>
    auto SingleMixin<TQuery>::Single(const TPredicate predicate) const -> ValueType
    {
        const std::optional<ValueType> value = MixinUtilities::GetQuery<TQuery>(*this).SingleOptional(predicate);
        if (!value)
        {
            throw Exceptions::EmptyCollectionException();
        }

        return *value;
    }
}