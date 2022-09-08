#pragma once

#include "Details/Enumerators/OrderEnumerator.Forward.hpp"

#include "Details/Containers/ConstIteratorProvider.hpp"
#include "Details/Containers/SortContainerStrategy.hpp"
#include "Details/Containers/VectorContainerProvider.hpp"
#include "Details/Enumerators/ContainerEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    struct OrderEnumerator final : ContainerEnumerator<TEnumerator, Containers::VectorContainerProvider, Containers::ConstIteratorProvider, Containers::SortContainerStrategy>
    {
        using Base = ContainerEnumerator<TEnumerator, Containers::VectorContainerProvider, Containers::ConstIteratorProvider, Containers::SortContainerStrategy>;

        OrderEnumerator(const Query<TEnumerator>& query);
    };
}