#pragma once

#include "Details/Enumerators/ZipEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct ZipMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;

        template <typename TZipEnumerator, typename TResultSelector>
        auto Zip(const Query<TZipEnumerator>& zipQuery, const TResultSelector resultSelector) const -> Query<Enumerators::ZipEnumerator<EnumeratorType, TZipEnumerator, TResultSelector>>;
    };
}