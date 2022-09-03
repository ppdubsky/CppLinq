#pragma once

#include "Details/Enumerators/ReverseEnumerator.Forward.hpp"

#include "Details/Collections/ConstReverseIteratorProvider.hpp"
#include "Details/Collections/VectorCollectionProvider.hpp"
#include "Details/Enumerators/CollectionEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    struct ReverseEnumerator final : CollectionEnumerator<TEnumerator, Collections::VectorCollectionProvider, Collections::ConstReverseIteratorProvider>
    {
        using Base = CollectionEnumerator<TEnumerator, Collections::VectorCollectionProvider, Collections::ConstReverseIteratorProvider>;

        ReverseEnumerator(const Query<TEnumerator>& query);
    };
}