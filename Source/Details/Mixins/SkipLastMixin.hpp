#pragma once

#include <cstdint>

#include "Details/Enumerators/SkipLastEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct SkipLastMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;

        auto SkipLast(const std::uint32_t count) const -> Query<Enumerators::SkipLastEnumerator<EnumeratorType>>;
    };
}