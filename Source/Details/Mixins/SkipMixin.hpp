#pragma once

#include <cstdint>

#include "Details/Enumerators/SkipEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct SkipMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;

        auto Skip(const std::uint32_t count) const -> Query<Enumerators::SkipEnumerator<EnumeratorType>>;
    };
}