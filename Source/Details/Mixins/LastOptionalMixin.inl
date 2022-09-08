#pragma once

#include "Details/Mixins/LastOptionalMixin.hpp"

#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Predicates/TruePredicate.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto LastOptionalMixin<TQuery>::LastOptional() const -> std::optional<ValueType>
    {
        return LastOptional(Predicates::TruePredicate<ValueType>());
    }

    template <typename TQuery>
    template <typename TPredicate>
    auto LastOptionalMixin<TQuery>::LastOptional(const TPredicate predicate) const -> std::optional<ValueType>
    {
        std::optional<ValueType> value;

        EnumeratorType enumerator = MixinUtilities::GetEnumerator<TQuery>(*this);
        while (enumerator.HasCurrent())
        {
            const ValueType current = enumerator.GetCurrent();
            if (predicate(current))
            {
                value = current;
            }

            enumerator.MoveNext();
        }

        return value;
    }
}