#pragma once

#include "Details/Mixins/FirstOptionalMixin.hpp"

#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Predicates/TruePredicate.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto FirstOptionalMixin<TQuery>::FirstOptional() const -> std::optional<ValueType>
    {
        return FirstOptional(Predicates::TruePredicate<ValueType>());
    }

    template <typename TQuery>
    template <typename TPredicate>
    auto FirstOptionalMixin<TQuery>::FirstOptional(const TPredicate predicate) const -> std::optional<ValueType>
    {
        std::optional<ValueType> value;

        EnumeratorType enumerator = MixinUtilities::GetEnumerator<TQuery>(*this);
        while (enumerator.HasCurrent())
        {
            const ValueType current = enumerator.GetCurrent();
            if (predicate(current))
            {
                value = current;
                break;
            }

            enumerator.MoveNext();
        }

        return value;
    }
}