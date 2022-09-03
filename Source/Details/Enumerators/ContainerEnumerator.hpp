#pragma once

#include "Details/Enumerators/ContainerStrategies/DoNothingContainerStrategy.hpp"
#include "Details/Query.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator, template <typename> typename TContainerProvider, template <typename> typename TIteratorProvider, template <typename> typename TContainerStrategy = ContainerStrategies::DoNothingContainerStrategy>
    struct ContainerEnumerator
    {
        using ContainerType = typename TContainerProvider<TEnumerator>::ContainerType;
        using IteratorType = typename TIteratorProvider<ContainerType>::IteratorType;
        using ValueType = typename Query<TEnumerator>::ValueType;

        auto GetCurrent() -> const ValueType&;
        auto IsFinished() -> bool;
        void MoveNext();

    protected:
        ContainerEnumerator(const Query<TEnumerator>& query);

    private:
        void EnsureEnumeratorIsReady();

        IteratorType begin;
        ContainerType container;
        IteratorType end;
        bool isReady{ false };
        Query<TEnumerator> query;
    };
}