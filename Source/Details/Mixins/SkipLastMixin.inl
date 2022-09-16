#pragma once

#include "Details/Mixins/SkipLastMixin.hpp"

#include "Details/Enumerators/SkipLastEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto SkipLastMixin<TQuery>::SkipLast(const std::uint32_t count) const -> Query<Enumerators::SkipLastEnumerator<EnumeratorType>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), count } };
    }
}