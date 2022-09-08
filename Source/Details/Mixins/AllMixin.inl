#pragma once

#include "Details/Mixins/AllMixin.hpp"

#include "Details/Mixins/MixinUtilities.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TPredicate>
    auto AllMixin<TQuery>::All(const TPredicate predicate) const -> bool
    {
        auto isValid = true;

        EnumeratorType enumerator = MixinUtilities::GetEnumerator<TQuery>(*this);
        while (enumerator.HasCurrent())
        {
            if (!predicate(enumerator.GetCurrent()))
            {
                isValid = false;
                break;
            }

            enumerator.MoveNext();
        }

        return isValid;
    }
}