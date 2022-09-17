#pragma once

#include "Details/Query.Forward.hpp"

#include "Details/Loops/LoopIterator.Forward.hpp"
#include "Details/Loops/LoopIteratorSentinel.Forward.hpp"

#include "Details/Mixins/AggregateMixin.hpp"
#include "Details/Mixins/AllMixin.hpp"
#include "Details/Mixins/AnyMixin.hpp"
#include "Details/Mixins/AppendMixin.hpp"
#include "Details/Mixins/AverageMixin.hpp"
#include "Details/Mixins/ChunkMixin.hpp"
#include "Details/Mixins/ConcatenateMixin.hpp"
#include "Details/Mixins/ContainsMixin.hpp"
#include "Details/Mixins/CountMixin.hpp"
#include "Details/Mixins/DefaultIfEmptyMixin.hpp"
#include "Details/Mixins/DistinctByMixin.hpp"
#include "Details/Mixins/DistinctMixin.hpp"
#include "Details/Mixins/ElementAtMixin.hpp"
#include "Details/Mixins/ElementAtOptionalMixin.hpp"
#include "Details/Mixins/ElementAtOrDefaultMixin.hpp"
#include "Details/Mixins/ExceptByMixin.hpp"
#include "Details/Mixins/ExceptMixin.hpp"
#include "Details/Mixins/FirstMixin.hpp"
#include "Details/Mixins/FirstOptionalMixin.hpp"
#include "Details/Mixins/FirstOrDefaultMixin.hpp"
#include "Details/Mixins/ForEachMixin.hpp"
#include "Details/Mixins/IntersectByMixin.hpp"
#include "Details/Mixins/IntersectMixin.hpp"
#include "Details/Mixins/LastMixin.hpp"
#include "Details/Mixins/LastOptionalMixin.hpp"
#include "Details/Mixins/LastOrDefaultMixin.hpp"
#include "Details/Mixins/MaximumByMixin.hpp"
#include "Details/Mixins/MaximumMixin.hpp"
#include "Details/Mixins/MinimumMixin.hpp"
#include "Details/Mixins/OrderByMixin.hpp"
#include "Details/Mixins/PrependMixin.hpp"
#include "Details/Mixins/QueryMixins.hpp"
#include "Details/Mixins/ReverseMixin.hpp"
#include "Details/Mixins/SelectManyMixin.hpp"
#include "Details/Mixins/SelectMixin.hpp"
#include "Details/Mixins/SequenceEqualMixin.hpp"
#include "Details/Mixins/SingleMixin.hpp"
#include "Details/Mixins/SingleOptionalMixin.hpp"
#include "Details/Mixins/SingleOrDefaultMixin.hpp"
#include "Details/Mixins/SkipLastMixin.hpp"
#include "Details/Mixins/SkipLastWhileMixin.hpp"
#include "Details/Mixins/SkipMixin.hpp"
#include "Details/Mixins/SkipWhileMixin.hpp"
#include "Details/Mixins/StaticCastMixin.hpp"
#include "Details/Mixins/SumMixin.hpp"
#include "Details/Mixins/TakeLastMixin.hpp"
#include "Details/Mixins/TakeLastWhileMixin.hpp"
#include "Details/Mixins/TakeMixin.hpp"
#include "Details/Mixins/TakeWhileMixin.hpp"
#include "Details/Mixins/ToVectorMixin.hpp"
#include "Details/Mixins/UnionByMixin.hpp"
#include "Details/Mixins/UnionMixin.hpp"
#include "Details/Mixins/WhereMixin.hpp"
#include "Details/Mixins/ZipMixin.hpp"

namespace CppLinq::Details
{
    template <typename TEnumerator>
    struct Query final :
        Mixins::QueryMixins<
            Query<TEnumerator>,
            Mixins::AggregateMixin,
            Mixins::AllMixin,
            Mixins::AnyMixin,
            Mixins::AppendMixin,
            Mixins::AverageMixin,
            Mixins::ChunkMixin,
            Mixins::ConcatenateMixin,
            Mixins::ContainsMixin,
            Mixins::CountMixin,
            Mixins::DefaultIfEmptyMixin,
            Mixins::DistinctByMixin,
            Mixins::DistinctMixin,
            Mixins::ElementAtMixin,
            Mixins::ElementAtOptionalMixin,
            Mixins::ElementAtOrDefaultMixin,
            Mixins::ExceptByMixin,
            Mixins::ExceptMixin,
            Mixins::FirstMixin,
            Mixins::FirstOptionalMixin,
            Mixins::FirstOrDefaultMixin,
            Mixins::ForEachMixin,
            Mixins::IntersectByMixin,
            Mixins::IntersectMixin,
            Mixins::LastMixin,
            Mixins::LastOptionalMixin,
            Mixins::LastOrDefaultMixin,
            Mixins::MaximumByMixin,
            Mixins::MaximumMixin,
            Mixins::MinimumMixin,
            Mixins::OrderByMixin,
            Mixins::PrependMixin,
            Mixins::ReverseMixin,
            Mixins::SelectManyMixin,
            Mixins::SelectMixin,
            Mixins::SequenceEqualMixin,
            Mixins::SingleMixin,
            Mixins::SingleOptionalMixin,
            Mixins::SingleOrDefaultMixin,
            Mixins::SkipLastMixin,
            Mixins::SkipLastWhileMixin,
            Mixins::SkipMixin,
            Mixins::SkipWhileMixin,
            Mixins::StaticCastMixin,
            Mixins::SumMixin,
            Mixins::TakeLastMixin,
            Mixins::TakeLastWhileMixin,
            Mixins::TakeMixin,
            Mixins::TakeWhileMixin,
            Mixins::ToVectorMixin,
            Mixins::UnionByMixin,
            Mixins::UnionMixin,
            Mixins::WhereMixin,
            Mixins::ZipMixin
        >
    {
        Query(const TEnumerator enumerator);

        auto GetEnumerator() const -> const TEnumerator&;

    private:
        TEnumerator enumerator;
    };

    template <typename TEnumerator>
    auto begin(const Query<TEnumerator>& query) -> Loops::LoopIterator<TEnumerator>;
    template <typename TEnumerator>
    auto end(const Query<TEnumerator>& query) -> Loops::LoopIteratorSentinel;
}