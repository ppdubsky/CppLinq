#pragma once

#include "Details/Mixins/AverageMixin.hpp"

#include "Details/Mixins/MixinUtilities.hpp"
#include "Exceptions/EmptyCollectionException.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto AverageMixin<TQuery>::Average() const -> ValueType
    {
        auto sum = static_cast<ValueType>(0);
        auto count = 0U;

        EnumeratorType enumerator = MixinUtilities::GetEnumerator<TQuery>(*this);
        while (enumerator.HasCurrent())
        {
            sum += enumerator.GetCurrent();

            ++count;

            enumerator.MoveNext();
        }

        if (count == 0U)
        {
            throw Exceptions::EmptyCollectionException();
        }

        return sum / count;
    }
}