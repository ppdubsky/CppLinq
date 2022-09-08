#pragma once

#include "Details/Mixins/ChunkMixin.hpp"

#include "Details/Enumerators/ChunkEnumerator.hpp"
#include "Details/Mixins/MixinUtilities.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Mixins
{
    template <typename TQuery>
    auto ChunkMixin<TQuery>::Chunk(const std::uint32_t size) const -> Query<Enumerators::ChunkEnumerator<EnumeratorType>>
    {
        return { { MixinUtilities::GetEnumerator<TQuery>(*this), size } };
    }
}