#pragma once

#include "Details/Mixins/ZipMixin.hpp"

#include "Details/Enumerators/ZipEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TZipEnumerator, typename TResultSelector>
    auto ZipMixin<TQuery>::Zip(const Query<TZipEnumerator>& zipQuery, const TResultSelector resultSelector) const -> Query<Enumerators::ZipEnumerator<EnumeratorType, TZipEnumerator, TResultSelector>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), zipQuery.GetEnumerator(), resultSelector } };
    }
}