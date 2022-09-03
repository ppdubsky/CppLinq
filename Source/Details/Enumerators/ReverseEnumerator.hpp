#pragma once

#include "Details/Enumerators/EnumeratorWrapper.hpp"
#include "Details/Enumerators/IteratorEnumerator.hpp"

namespace CppLinq::Details::Enumerators
{
    template <typename TContainer, typename TIterator>
    struct ReverseEnumerator final : EnumeratorWrapper<IteratorEnumerator<TIterator>>
    {
        using Base = EnumeratorWrapper<IteratorEnumerator<TIterator>>;

        ReverseEnumerator(const TContainer& container) ;

    private:
        TContainer container;
    };
}