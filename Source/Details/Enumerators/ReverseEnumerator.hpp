#pragma once

#include "Details/Enumerators/ReverseEnumerator.Forward.hpp"

#include "Details/Enumerators/ContainerEnumerator.hpp"
#include "Details/Enumerators/ContainerProviders/VectorContainerProvider.hpp"
#include "Details/Enumerators/IteratorProviders/ConstReverseIteratorProvider.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    struct ReverseEnumerator final : ContainerEnumerator<TEnumerator, ContainerProviders::VectorContainerProvider, IteratorProviders::ConstReverseIteratorProvider>
    {
        using Base = ContainerEnumerator<TEnumerator, ContainerProviders::VectorContainerProvider, IteratorProviders::ConstReverseIteratorProvider>;

        ReverseEnumerator(const Query<TEnumerator>& query);
    };
}