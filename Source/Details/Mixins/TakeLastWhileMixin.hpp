#pragma once

#include "Details/Enumerators/TakeLastWhileEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct TakeLastWhileMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;

        template <typename TPredicate>
        auto TakeLastWhile(const TPredicate predicate) const -> Query<Enumerators::TakeLastWhileEnumerator<EnumeratorType, TPredicate>>;
    };
}