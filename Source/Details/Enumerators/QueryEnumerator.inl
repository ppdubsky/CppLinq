#pragma once

#include "Details/Enumerators/QueryEnumerator.hpp"

#include "Exceptions/FinishedEnumeratorException.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, template <typename> typename TContainerProvider, template <typename> typename TIteratorProvider, template <typename> typename TContainerStrategy>
    QueryEnumerator<TEnumerator, TContainerProvider, TIteratorProvider, TContainerStrategy>::QueryEnumerator(const Query<TEnumerator>& query) :
        query(query)
    {
    }

    template <typename TEnumerator, template <typename> typename TContainerProvider, template <typename> typename TIteratorProvider, template <typename> typename TContainerStrategy>
    void QueryEnumerator<TEnumerator, TContainerProvider, TIteratorProvider, TContainerStrategy>::EnsureEnumeratorIsReady()
    {
        if (!isReady)
        {
            container = TContainerProvider<TEnumerator>::GetContainer(query);

            TContainerStrategy<ContainerType>::PrepareContainer(container);

            begin = TIteratorProvider<ContainerType>::GetBegin(container);
            end = TIteratorProvider<ContainerType>::GetEnd(container);

            isReady = true;
        }
    }

    template <typename TEnumerator, template <typename> typename TContainerProvider, template <typename> typename TIteratorProvider, template <typename> typename TContainerStrategy>
    auto QueryEnumerator<TEnumerator, TContainerProvider, TIteratorProvider, TContainerStrategy>::GetCurrent() -> const ValueType&
    {
        EnsureEnumeratorIsReady();

        if (!HasCurrent())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        return *begin;
    }

    template <typename TEnumerator, template <typename> typename TContainerProvider, template <typename> typename TIteratorProvider, template <typename> typename TContainerStrategy>
    auto QueryEnumerator<TEnumerator, TContainerProvider, TIteratorProvider, TContainerStrategy>::HasCurrent() -> bool
    {
        EnsureEnumeratorIsReady();

        return begin != end;
    }

    template <typename TEnumerator, template <typename> typename TContainerProvider, template <typename> typename TIteratorProvider, template <typename> typename TContainerStrategy>
    void QueryEnumerator<TEnumerator, TContainerProvider, TIteratorProvider, TContainerStrategy>::MoveNext()
    {
        EnsureEnumeratorIsReady();

        if (!HasCurrent())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        ++begin;
    }
}