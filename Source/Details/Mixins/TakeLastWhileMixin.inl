#pragma once

#include "Details/Mixins/TakeLastWhileMixin.hpp"

#include "Details/Enumerators/TakeLastWhileEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TPredicate>
    auto TakeLastWhileMixin<TQuery>::TakeLastWhile(const TPredicate predicate) const -> Query<Enumerators::TakeLastWhileEnumerator<EnumeratorType, TPredicate>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), predicate } };
    }
}