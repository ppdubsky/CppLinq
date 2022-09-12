#pragma once

#include "Details/Enumerators/ReverseEnumerator.Forward.hpp"

#include "Details/Containers/ConstReverseIteratorProvider.hpp"
#include "Details/Containers/VectorContainerProvider.hpp"
#include "Details/Enumerators/QueryEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    struct ReverseEnumerator final : QueryEnumerator<TEnumerator, Containers::VectorContainerProvider, Containers::ConstReverseIteratorProvider>
    {
        using Base = QueryEnumerator<TEnumerator, Containers::VectorContainerProvider, Containers::ConstReverseIteratorProvider>;

        ReverseEnumerator(const Query<TEnumerator>& query);
    };
}