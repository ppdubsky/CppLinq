#pragma once

#include "Details/Enumerators/StaticCastEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct StaticCastMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;

        template <typename TNewType>
        auto StaticCast() const -> Query<Enumerators::StaticCastEnumerator<EnumeratorType, TNewType>>;
    };
}