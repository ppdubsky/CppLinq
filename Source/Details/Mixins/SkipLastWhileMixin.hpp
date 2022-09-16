#pragma once

#include "Details/Enumerators/SkipLastWhileEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct SkipLastWhileMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;

        template <typename TPredicate>
        auto SkipLastWhile(const TPredicate predicate) const -> Query<Enumerators::SkipLastWhileEnumerator<EnumeratorType, TPredicate>>;
    };
}