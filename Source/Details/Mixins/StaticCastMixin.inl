#pragma once

#include "Details/Mixins/StaticCastMixin.hpp"

#include "Details/Enumerators/StaticCastEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TNewType>
    auto StaticCastMixin<TQuery>::StaticCast() const -> Query<Enumerators::StaticCastEnumerator<EnumeratorType, TNewType>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this) } };
    }
}