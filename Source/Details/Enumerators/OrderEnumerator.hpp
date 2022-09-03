#pragma once

#include "Details/Enumerators/OrderEnumerator.Forward.hpp"

#include "Details/Collections/ConstIteratorProvider.hpp"
#include "Details/Collections/SortCollectionStrategy.hpp"
#include "Details/Collections/VectorCollectionProvider.hpp"
#include "Details/Enumerators/CollectionEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TEnumerator>
    struct OrderEnumerator final : CollectionEnumerator<TEnumerator, Collections::VectorCollectionProvider, Collections::ConstIteratorProvider, Collections::SortCollectionStrategy>
    {
        using Base = CollectionEnumerator<TEnumerator, Collections::VectorCollectionProvider, Collections::ConstIteratorProvider, Collections::SortCollectionStrategy>;

        OrderEnumerator(const Query<TEnumerator>& query);
    };
}