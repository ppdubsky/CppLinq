#pragma once

#include <cstdint>

#include "Details/Enumerators/TakeEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct TakeMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;

        auto Take(const std::uint32_t count) const -> Query<Enumerators::TakeEnumerator<EnumeratorType>>;
    };
}