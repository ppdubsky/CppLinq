#pragma once

#include "Details/Enumerators/DefaultIfEmptyEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct DefaultIfEmptyMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        using ValueType = typename EnumeratorType::ValueType;

        auto DefaultIfEmpty() const -> Query<Enumerators::DefaultIfEmptyEnumerator<EnumeratorType>>;
        auto DefaultIfEmpty(const ValueType& defaultValue) const -> Query<Enumerators::DefaultIfEmptyEnumerator<EnumeratorType>>;
    };
}