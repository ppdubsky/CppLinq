#pragma once

#include "Details/Mixins/MinimumByMixin.hpp"

#include "Details/Mixins/MixinUtilities.hpp"
#include "Exceptions/EmptyContainerException.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TSelector>
    auto MinimumByMixin<TQuery>::MinimumBy(const TSelector selector) const -> ValueType
    {
        EnumeratorType enumerator = MixinUtilities::GetEnumerator<TQuery>(*this);
        if (!enumerator.HasCurrent())
        {
            throw Exceptions::EmptyContainerException();
        }

        ValueType bound = enumerator.GetCurrent();

        enumerator.MoveNext();

        while (enumerator.HasCurrent())
        {
            const ValueType current = enumerator.GetCurrent();
            if (selector(current) < selector(bound))
            {
                bound = current;
            }

            enumerator.MoveNext();
        }

        return bound;
    }
}