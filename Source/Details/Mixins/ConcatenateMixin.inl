#pragma once

#include "Details/Mixins/ConcatenateMixin.hpp"

#include "Details/Enumerators/ConcatenationEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TSecondEnumerator>
    auto ConcatenateMixin<TQuery>::Concatenate(const Query<TSecondEnumerator>& secondQuery) const -> Query<Enumerators::ConcatenationEnumerator<EnumeratorType, TSecondEnumerator>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), secondQuery.GetEnumerator() } };
    }
}