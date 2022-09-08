#pragma once

#include "Details/Mixins/CountMixin.hpp"

#include "Details/Mixins/MixinUtilities.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto CountMixin<TQuery>::Count() const -> std::uint32_t
    {
        return Count([](const ValueType& /*value*/){ return true; });
    }

    template <typename TQuery>
    template <typename TPredicate>
    auto CountMixin<TQuery>::Count(const TPredicate predicate) const -> std::uint32_t
    {
        auto count = 0U;

        EnumeratorType enumerator = MixinUtilities::GetEnumerator<TQuery>(*this);
        while (enumerator.HasCurrent())
        {
            if (predicate(enumerator.GetCurrent()))
            {
                ++count;
            }

            enumerator.MoveNext();
        }

        return count;
    }
}