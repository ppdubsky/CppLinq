#pragma once

#include "Details/Mixins/WhereMixin.hpp"

#include "Details/Enumerators/WhereEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TPredicate>
    auto WhereMixin<TQuery>::Where(const TPredicate predicate) const -> Query<Enumerators::WhereEnumerator<EnumeratorType, TPredicate>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), predicate } };
    }
}