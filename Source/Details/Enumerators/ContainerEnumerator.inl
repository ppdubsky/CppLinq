#pragma once

#include "Details/Enumerators/ContainerEnumerator.hpp"
#include "Exceptions/FinishedEnumeratorException.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, template <typename> typename TContainerProvider, template <typename> typename TIteratorProvider, template <typename> typename TContainerStrategy>
    ContainerEnumerator<TEnumerator, TContainerProvider, TIteratorProvider, TContainerStrategy>::ContainerEnumerator(const Query<TEnumerator>& query) :
        query(query)
    {
    }

    template <typename TEnumerator, template <typename> typename TContainerProvider, template <typename> typename TIteratorProvider, template <typename> typename TContainerStrategy>
    void ContainerEnumerator<TEnumerator, TContainerProvider, TIteratorProvider, TContainerStrategy>::EnsureEnumeratorIsReady()
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
    auto ContainerEnumerator<TEnumerator, TContainerProvider, TIteratorProvider, TContainerStrategy>::GetCurrent() -> const ValueType&
    {
        EnsureEnumeratorIsReady();

        if (IsFinished())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        return *begin;
    }

    template <typename TEnumerator, template <typename> typename TContainerProvider, template <typename> typename TIteratorProvider, template <typename> typename TContainerStrategy>
    auto ContainerEnumerator<TEnumerator, TContainerProvider, TIteratorProvider, TContainerStrategy>::IsFinished() -> bool
    {
        EnsureEnumeratorIsReady();

        return begin == end;
    }

    template <typename TEnumerator, template <typename> typename TContainerProvider, template <typename> typename TIteratorProvider, template <typename> typename TContainerStrategy>
    void ContainerEnumerator<TEnumerator, TContainerProvider, TIteratorProvider, TContainerStrategy>::MoveNext()
    {
        EnsureEnumeratorIsReady();

        if (IsFinished())
        {
            throw Exceptions::FinishedEnumeratorException();
        }

        ++begin;
    }
}