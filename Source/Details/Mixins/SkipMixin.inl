#pragma once

#include "Details/Mixins/SkipMixin.hpp"

#include "Details/Enumerators/SkipEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto SkipMixin<TQuery>::Skip(const std::uint32_t count) const -> Query<Enumerators::SkipEnumerator<EnumeratorType>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), count } };
    }
}