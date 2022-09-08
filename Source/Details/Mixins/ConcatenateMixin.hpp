#pragma once

#include "Details/Enumerators/ConcatenationEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct ConcatenateMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;

        template <typename TNextEnumerator>
        auto Concatenate(const Query<TNextEnumerator>& nextQuery) const -> Query<Enumerators::ConcatenationEnumerator<EnumeratorType, TNextEnumerator>>;
    };
}