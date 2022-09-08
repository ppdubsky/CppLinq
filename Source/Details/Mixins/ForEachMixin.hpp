#pragma once

#include "Details/Enumerators/ForEachEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct ForEachMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;

        template <typename TFunction>
        auto ForEach(const TFunction function) const -> Query<Enumerators::ForEachEnumerator<EnumeratorType, TFunction>>;
    };
}