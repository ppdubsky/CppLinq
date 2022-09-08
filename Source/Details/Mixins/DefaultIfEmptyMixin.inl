#pragma once

#include "Details/Mixins/DefaultIfEmptyMixin.hpp"

#include "Details/Enumerators/DefaultIfEmptyEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto DefaultIfEmptyMixin<TQuery>::DefaultIfEmpty() const -> Query<Enumerators::DefaultIfEmptyEnumerator<EnumeratorType>>
    {
        return DefaultIfEmpty(ValueType());
    }
    template <typename TQuery>
    auto DefaultIfEmptyMixin<TQuery>::DefaultIfEmpty(const ValueType& defaultValue) const -> Query<Enumerators::DefaultIfEmptyEnumerator<EnumeratorType>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), defaultValue } };
    }
}