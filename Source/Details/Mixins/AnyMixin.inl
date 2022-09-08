#pragma once

#include "Details/Mixins/AnyMixin.hpp"

#include "Details/Mixins/MixinUtilities.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TPredicate>
    auto AnyMixin<TQuery>::Any(const TPredicate predicate) const -> bool
    {
        auto isValid = false;

        EnumeratorType enumerator = MixinUtilities::GetEnumerator<TQuery>(*this);
        while (enumerator.HasCurrent())
        {
            if (predicate(enumerator.GetCurrent()))
            {
                isValid = true;
                break;
            }

            enumerator.MoveNext();
        }

        return isValid;
    }
}