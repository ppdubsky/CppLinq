#pragma once

#include "Details/Mixins/SkipLastWhileMixin.hpp"

#include "Details/Enumerators/SkipLastWhileEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TPredicate>
    auto SkipLastWhileMixin<TQuery>::SkipLastWhile(const TPredicate predicate) const -> Query<Enumerators::SkipLastWhileEnumerator<EnumeratorType, TPredicate>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), predicate } };
    }
}