#pragma once

#include "Details/Mixins/ConcatenateMixin.hpp"

#include "Details/Enumerators/ConcatenationEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TNextEnumerator>
    auto ConcatenateMixin<TQuery>::Concatenate(const Query<TNextEnumerator>& nextQuery) const -> Query<Enumerators::ConcatenationEnumerator<EnumeratorType, TNextEnumerator>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), nextQuery.GetEnumerator() } };
    }
}