#pragma once

#include "Details/Mixins/ZipMixin.hpp"

#include "Details/Enumerators/ZipEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    template <typename TZipEnumerator, typename TSelector>
    auto ZipMixin<TQuery>::Zip(const Query<TZipEnumerator>& zipQuery, const TSelector selector) const -> Query<Enumerators::ZipEnumerator<EnumeratorType, TZipEnumerator, TSelector>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), zipQuery.GetEnumerator(), selector } };
    }
}