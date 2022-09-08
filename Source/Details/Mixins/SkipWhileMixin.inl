#pragma once

#include "Details/Mixins/SkipWhileMixin.hpp"

#include "Details/Enumerators/SkipWhileEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TPredicate>
    auto SkipWhileMixin<TQuery>::SkipWhile(const TPredicate predicate) const -> Query<Enumerators::SkipWhileEnumerator<EnumeratorType, TPredicate>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), predicate } };
    }
}