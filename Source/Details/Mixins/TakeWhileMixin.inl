#pragma once

#include "Details/Mixins/TakeWhileMixin.hpp"

#include "Details/Enumerators/TakeWhileEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TPredicate>
    auto TakeWhileMixin<TQuery>::TakeWhile(const TPredicate predicate) const -> Query<Enumerators::TakeWhileEnumerator<EnumeratorType, TPredicate>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), predicate } };
    }
}