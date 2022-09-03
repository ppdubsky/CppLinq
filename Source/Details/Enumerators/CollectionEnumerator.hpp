#pragma once

#include "Details/Collections/DoNothingCollectionStrategy.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, template <typename> typename TCollectionProvider, template <typename> typename TIteratorProvider, template <typename> typename TCollectionStrategy = Collections::DoNothingCollectionStrategy>
    struct CollectionEnumerator
    {
        using CollectionType = typename TCollectionProvider<TEnumerator>::CollectionType;
        using IteratorType = typename TIteratorProvider<CollectionType>::IteratorType;
        using ValueType = typename Query<TEnumerator>::ValueType;

        auto GetCurrent() -> const ValueType&;
        auto IsFinished() -> bool;
        void MoveNext();

    protected:
        CollectionEnumerator(const Query<TEnumerator>& query);

    private:
        void EnsureEnumeratorIsReady();

        IteratorType begin;
        CollectionType collection;
        IteratorType end;
        bool isReady{ false };
        Query<TEnumerator> query;
    };
}