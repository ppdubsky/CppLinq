#pragma once

#include "Details/Collections/ConstIteratorProvider.inl"
#include "Details/Collections/ConstReverseIteratorProvider.inl"
#include "Details/Collections/DoNothingCollectionStrategy.inl"
#include "Details/Collections/SortCollectionStrategy.inl"
#include "Details/Collections/VectorCollectionProvider.inl"
#include "Details/Enumerators/AppendEnumerator.inl"
#include "Details/Enumerators/ChunkEnumerator.inl"
#include "Details/Enumerators/CollectionEnumerator.inl"
#include "Details/Enumerators/ConcatenationEnumerator.inl"
#include "Details/Enumerators/DefaultIfEmptyEnumerator.inl"
#include "Details/Enumerators/EnumeratorWrapper.inl"
#include "Details/Enumerators/ForEachEnumerator.inl"
#include "Details/Enumerators/IteratorEnumerator.inl"
#include "Details/Enumerators/OrderEnumerator.inl"
#include "Details/Enumerators/PrependEnumerator.inl"
#include "Details/Enumerators/ReverseEnumerator.inl"
#include "Details/Enumerators/SelectEnumerator.inl"
#include "Details/Enumerators/SkipEnumerator.inl"
#include "Details/Enumerators/SkipWhileEnumerator.inl"
#include "Details/Enumerators/StaticCastEnumerator.inl"
#include "Details/Enumerators/TakeEnumerator.inl"
#include "Details/Enumerators/TakeWhileEnumerator.inl"
#include "Details/Enumerators/WhereEnumerator.inl"
#include "Details/Loops/LoopIterator.inl"
#include "Details/Mixins/AggregateMixin.inl"
#include "Details/Mixins/AllMixin.inl"
#include "Details/Mixins/AnyMixin.inl"
#include "Details/Mixins/AppendMixin.inl"
#include "Details/Mixins/AverageMixin.inl"
#include "Details/Mixins/ChunkMixin.inl"
#include "Details/Mixins/ConcatenateMixin.inl"
#include "Details/Mixins/CountMixin.inl"
#include "Details/Mixins/DefaultIfEmptyMixin.inl"
#include "Details/Mixins/FirstMixin.inl"
#include "Details/Mixins/FirstOptionalMixin.inl"
#include "Details/Mixins/FirstOrDefaultMixin.inl"
#include "Details/Mixins/ForEachMixin.inl"
#include "Details/Mixins/LastMixin.inl"
#include "Details/Mixins/LastOptionalMixin.inl"
#include "Details/Mixins/LastOrDefaultMixin.inl"
#include "Details/Mixins/MaximumMixin.inl"
#include "Details/Mixins/MinimumMixin.inl"
#include "Details/Mixins/MixinUtilities.inl"
#include "Details/Mixins/OrderByMixin.inl"
#include "Details/Mixins/PrependMixin.inl"
#include "Details/Mixins/ReverseMixin.inl"
#include "Details/Mixins/SelectMixin.inl"
#include "Details/Mixins/SingleMixin.inl"
#include "Details/Mixins/SingleOptionalMixin.inl"
#include "Details/Mixins/SingleOrDefaultMixin.inl"
#include "Details/Mixins/SkipMixin.inl"
#include "Details/Mixins/SkipWhileMixin.inl"
#include "Details/Mixins/StaticCastMixin.inl"
#include "Details/Mixins/SumMixin.inl"
#include "Details/Mixins/TakeMixin.inl"
#include "Details/Mixins/TakeWhileMixin.inl"
#include "Details/Mixins/ToVectorMixin.inl"
#include "Details/Mixins/WhereMixin.inl"
#include "Details/Query.inl"

namespace CppLinq
{
    template <typename TCollection>
    auto From(const TCollection& collection) -> Details::Query<Details::Enumerators::IteratorEnumerator<typename TCollection::const_iterator>>
    {
        return { { collection.cbegin(), collection.cend() } };
    }

    template <typename T, std::uint32_t TLength>
    auto From(const T (&array)[TLength]) -> Details::Query<Details::Enumerators::IteratorEnumerator<const T*>>
    {
        return { { reinterpret_cast<const T*>(&array), reinterpret_cast<const T*>(&array) + TLength } };
    }
}