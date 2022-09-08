#pragma once

#include "Details/Enumerators/ReverseEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct ReverseMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;

        auto Reverse() const -> Query<Enumerators::ReverseEnumerator<EnumeratorType>>;
    };
}