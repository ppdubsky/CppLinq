#pragma once

#include "Details/Mixins/OrderByMixin.hpp"

#include "Details/Enumerators/OrderEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto OrderByMixin<TQuery>::OrderBy() const -> Query<Enumerators::OrderEnumerator<EnumeratorType>>
    {
        return { { MixinUtilities::GetQuery<TQuery>(*this) } };
    }
}