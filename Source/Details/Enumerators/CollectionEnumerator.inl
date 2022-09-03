#pragma once

#include "Details/Enumerators/CollectionEnumerator.hpp"
#include "Exceptions/FinishedEnumeratorException.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, template <typename> typename TCollectionProvider, template <typename> typename TIteratorProvider, template <typename> typename TCollectionStrategy>
    CollectionEnumerator<TEnumerator, TCollectionProvider, TIteratorProvider, TCollectionStrategy>::CollectionEnumerator(const Query<TEnumerator>& query) :
        query(query)
    {
    }

    template <typename TEnumerator, template <typename> typename TCollectionProvider, template <typename> typename TIteratorProvider, template <typename> typename TCollectionStrategy>
    void CollectionEnumerator<TEnumerator, TCollectionProvider, TIteratorProvider, TCollectionStrategy>::EnsureEnumeratorIsReady()
    {
        if (!isReady)
        {
            collection = TCollectionProvider<TEnumerator>::GetCollection(query);

            TCollectionStrategy<CollectionType>::PrepareCollection(collection);

            begin = TIteratorProvider<CollectionType>::GetBegin(collection);
            end = TIteratorProvider<CollectionType>::GetEnd(collection);

            isReady = true;
        }
    }

    template <typename TEnumerator, template <typename> typename TCollectionProvider, template <typename> typename TIteratorProvider, template <typename> typename TCollectionStrategy>
    auto CollectionEnumerator<TEnumerator, TCollectionProvider, TIteratorProvider, TCollectionStrategy>::GetCurrent() -> const ValueType&
    {
        EnsureEnumeratorIsReady();

        if (IsFinished())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        return *begin;
    }

    template <typename TEnumerator, template <typename> typename TCollectionProvider, template <typename> typename TIteratorProvider, template <typename> typename TCollectionStrategy>
    auto CollectionEnumerator<TEnumerator, TCollectionProvider, TIteratorProvider, TCollectionStrategy>::IsFinished() -> bool
    {
        EnsureEnumeratorIsReady();

        return begin == end;
    }

    template <typename TEnumerator, template <typename> typename TCollectionProvider, template <typename> typename TIteratorProvider, template <typename> typename TCollectionStrategy>
    void CollectionEnumerator<TEnumerator, TCollectionProvider, TIteratorProvider, TCollectionStrategy>::MoveNext()
    {
        EnsureEnumeratorIsReady();

        if (IsFinished())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        ++begin;
    }
}