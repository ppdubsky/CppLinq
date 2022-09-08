#pragma once

#include "Details/Mixins/MaximumMixin.hpp"

#include "Exceptions/EmptyCollectionException.hpp"
#include "Details/Mixins/MixinUtilities.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto MaximumMixin<TQuery>::Maximum() const -> ValueType
    {
        EnumeratorType enumerator = MixinUtilities::GetEnumerator<TQuery>(*this);
        if (!enumerator.HasCurrent())
        {
            throw Exceptions::EmptyCollectionException();
        }

        ValueType bound = enumerator.GetCurrent();

        enumerator.MoveNext();

        while (enumerator.HasCurrent())
        {
            const ValueType current = enumerator.GetCurrent();
            if (current > bound)
            {
                bound = current;
            }

            enumerator.MoveNext();
        }

        return bound;
    }
}