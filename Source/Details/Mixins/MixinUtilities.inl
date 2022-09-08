#pragma once

#include "Details/Mixins/MixinUtilities.hpp"

#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery, typename TMixin>
    auto MixinUtilities::GetEnumerator(const TMixin& mixin) -> typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType
    {
        return GetQuery<TQuery>(mixin).GetEnumerator();
    }

    template <typename TQuery, typename TMixin>
    auto MixinUtilities::GetQuery(const TMixin& mixin) -> const TQuery&
    {
        return static_cast<const TQuery&>(mixin);
    }
}