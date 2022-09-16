#pragma once

#include "Details/Mixins/TakeLastMixin.hpp"

#include "Details/Enumerators/TakeLastEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto TakeLastMixin<TQuery>::TakeLast(const std::uint32_t count) const -> Query<Enumerators::TakeLastEnumerator<EnumeratorType>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), count } };
    }
}