#pragma once

#include "Details/Enumerators/ContainerEnumerator.hpp"
#include "Details/Enumerators/ContainerProviders/VectorContainerProvider.hpp"
#include "Details/Enumerators/ContainerStrategies/SortContainerStrategy.hpp"
#include "Details/Enumerators/IteratorProviders/ConstIteratorProvider.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    struct OrderEnumerator final : ContainerEnumerator<TEnumerator, ContainerProviders::VectorContainerProvider, IteratorProviders::ConstIteratorProvider, ContainerStrategies::SortContainerStrategy>
    {
        using Base = ContainerEnumerator<TEnumerator, ContainerProviders::VectorContainerProvider, IteratorProviders::ConstIteratorProvider, ContainerStrategies::SortContainerStrategy>;

        OrderEnumerator(const Query<TEnumerator>& query);
    };
}