#pragma once

#include "Details/Mixins/ZipMixin.hpp"

#include "Details/Enumerators/ZipEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TSecondEnumerator, typename TResultSelector>
    auto ZipMixin<TQuery>::Zip(const Query<TSecondEnumerator>& secondQuery, const TResultSelector resultSelector) const -> Query<Enumerators::ZipEnumerator<EnumeratorType, TSecondEnumerator, TResultSelector>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), secondQuery.GetEnumerator(), resultSelector } };
    }
}