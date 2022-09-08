#pragma once

#include <cstdint>

#include "Details/Enumerators/ChunkEnumerator.Forward.hpp"
#include "Details/Query.Forward.hpp"

#include "Details/TypeTraits/EnumeratorTypeProvider.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    struct ChunkMixin
    {
        using EnumeratorType = typename TypeTraits::EnumeratorTypeProvider<TQuery>::EnumeratorType;

        auto Chunk(const std::uint32_t size) const -> Query<Enumerators::ChunkEnumerator<EnumeratorType>>;
    };
}