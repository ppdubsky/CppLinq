#pragma once

#include "Details/Enumerators/OrderEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct OrderByMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;

        auto OrderBy() const -> Query<Enumerators::OrderEnumerator<EnumeratorType>>;
    };
}