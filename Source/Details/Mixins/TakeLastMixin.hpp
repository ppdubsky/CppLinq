#pragma once

#include <cstdint>

#include "Details/Enumerators/TakeLastEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct TakeLastMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;

        auto TakeLast(const std::uint32_t count) const -> Query<Enumerators::TakeLastEnumerator<EnumeratorType>>;
    };
}