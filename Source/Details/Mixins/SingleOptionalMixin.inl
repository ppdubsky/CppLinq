#pragma once

#include "Details/Mixins/SingleOptionalMixin.hpp"

#include "Details/Mixins/MixinUtilities.hpp"
#include "Exceptions/MoreThanOneElementException.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto SingleOptionalMixin<TQuery>::SingleOptional() const -> std::optional<ValueType>
    {
        return SingleOptional([](const ValueType& /*value*/){ return true; });
    }

    template <typename TQuery>
    template <typename TPredicate>
    auto SingleOptionalMixin<TQuery>::SingleOptional(const TPredicate predicate) const -> std::optional<ValueType>
    {
        std::optional<ValueType> value;

        EnumeratorType enumerator = MixinUtilities::GetEnumerator<TQuery>(*this);
        while (enumerator.HasCurrent())
        {
            const ValueType current = enumerator.GetCurrent();
            if (predicate(current))
            {
                if (value)
                {
                    throw Exceptions::MoreThanOneElementException();
                }

                value = current;
            }

            enumerator.MoveNext();
        }

        return value;
    }
}