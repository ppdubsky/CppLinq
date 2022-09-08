#pragma once

#include "Details/Enumerators/SkipWhileEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct SkipWhileMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;

        template <typename TPredicate>
        auto SkipWhile(const TPredicate predicate) const -> Query<Enumerators::SkipWhileEnumerator<EnumeratorType, TPredicate>>;
    };
}