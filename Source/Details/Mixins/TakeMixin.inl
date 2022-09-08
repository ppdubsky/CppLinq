#pragma once

#include "Details/Mixins/TakeMixin.hpp"

#include "Details/Enumerators/TakeEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto TakeMixin<TQuery>::Take(const std::uint32_t count) const -> Query<Enumerators::TakeEnumerator<EnumeratorType>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), count } };
    }
}