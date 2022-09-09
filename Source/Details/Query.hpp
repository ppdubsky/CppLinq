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
#include "Details/Mixins/FirstMixin.hpp"
#include "Details/Mixins/FirstOptionalMixin.hpp"
#include "Details/Mixins/FirstOrDefaultMixin.hpp"
#include "Details/Mixins/ForEachMixin.hpp"
#include "Details/Mixins/LastMixin.hpp"
#include "Details/Mixins/LastOptionalMixin.hpp"
#include "Details/Mixins/LastOrDefaultMixin.hpp"
#include "Details/Mixins/MaximumMixin.hpp"
#include "Details/Mixins/MinimumMixin.hpp"
#include "Details/Mixins/OrderByMixin.hpp"
#include "Details/Mixins/PrependMixin.hpp"
#include "Details/Mixins/QueryMixins.hpp"
#include "Details/Mixins/ReverseMixin.hpp"
#include "Details/Mixins/SelectMixin.hpp"
#include "Details/Mixins/SingleMixin.hpp"
#include "Details/Mixins/SingleOptionalMixin.hpp"
#include "Details/Mixins/SingleOrDefaultMixin.hpp"
#include "Details/Mixins/SkipMixin.hpp"
#include "Details/Mixins/SkipWhileMixin.hpp"
#include "Details/Mixins/StaticCastMixin.hpp"
#include "Details/Mixins/SumMixin.hpp"
#include "Details/Mixins/TakeMixin.hpp"
#include "Details/Mixins/TakeWhileMixin.hpp"
#include "Details/Mixins/ToVectorMixin.hpp"
#include "Details/Mixins/WhereMixin.hpp"

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
            Mixins::FirstMixin,
            Mixins::FirstOptionalMixin,
            Mixins::FirstOrDefaultMixin,
            Mixins::ForEachMixin,
            Mixins::LastMixin,
            Mixins::LastOptionalMixin,
            Mixins::LastOrDefaultMixin,
            Mixins::MaximumMixin,
            Mixins::MinimumMixin,
            Mixins::OrderByMixin,
            Mixins::PrependMixin,
            Mixins::ReverseMixin,
            Mixins::SelectMixin,
            Mixins::SingleMixin,
            Mixins::SingleOptionalMixin,
            Mixins::SingleOrDefaultMixin,
            Mixins::SkipMixin,
            Mixins::SkipWhileMixin,
            Mixins::StaticCastMixin,
            Mixins::SumMixin,
            Mixins::TakeMixin,
            Mixins::TakeWhileMixin,
            Mixins::ToVectorMixin,
            Mixins::WhereMixin
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