#pragma once

#include "Details/Enumerators/TakeWhileEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct TakeWhileMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;

        template <typename TPredicate>
        auto TakeWhile(const TPredicate predicate) const -> Query<Enumerators::TakeWhileEnumerator<EnumeratorType, TPredicate>>;
    };
}