#pragma once

#include "Details/Enumerators/WhereEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct WhereMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;
        using ValueType = typename EnumeratorType::ValueType;

        template <typename TPredicate>
        auto Where(const TPredicate predicate) const -> Query<Enumerators::WhereEnumerator<EnumeratorType, TPredicate>>;
    };
}