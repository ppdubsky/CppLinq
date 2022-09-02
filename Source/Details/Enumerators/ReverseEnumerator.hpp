#pragma once

#include "EnumeratorWrapper.hpp"
#include "IteratorEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TContainer, typename TIterator = typename TContainer::const_reverse_iterator>
    struct ReverseEnumerator final : EnumeratorWrapper<IteratorEnumerator<TIterator>>
    {
        using Base = EnumeratorWrapper<IteratorEnumerator<TIterator>>;

        ReverseEnumerator(const TContainer& container) :
            Base({ container.crbegin(), container.crend() }),
            container(container)
        {
        }

    private:
        TContainer container;
    };
}