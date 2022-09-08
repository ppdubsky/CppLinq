#pragma once

#include "Details/Mixins/ForEachMixin.hpp"

#include "Details/Enumerators/ForEachEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TFunction>
    auto ForEachMixin<TQuery>::ForEach(const TFunction function) const -> Query<Enumerators::ForEachEnumerator<EnumeratorType, TFunction>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), function } };
    }
}